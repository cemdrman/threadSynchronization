#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

#define beklemeKoltukSayisi  3
#define maksimumBekleyenMusteriSayisi  4
#define tirasKoltugu 1

pthread_mutex_t tirasKoltuguLock;

struct koltuk{
  int thread_no;
  int doluMu;
}beklemeKoltugu[beklemeKoltukSayisi];

void *tirasOl(void* data){
    int time = *((int *) data);
    free(data);
    printf("%d. Thread tıraş oluyor...\n",time);
    sleep(time);
    printf("%d. Thread'in tıraşı bitti...\n",time);
    return NULL;
}


int main(int argc, char const *argv[]) {

  int threadSayisi = 10; //oluşacak max thread sayisi
  int counter = 1; //oluşan thread sayisini kontrol etmek için

  pthread_t thread;
  void * status;

  if (pthread_mutex_init(&tirasKoltuguLock, NULL) != 0)    {
        printf("\n mutex init hatasi\n");
        return 1;
  }

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

  while (counter <= threadSayisi) {

      beklemeKoltugu[counter].thread_no = counter;
      beklemeKoltugu[counter].doluMu = 1;
      int *sleepTime = malloc(sizeof(*sleepTime));
      *sleepTime = beklemeKoltugu[counter].thread_no;
      pthread_create(&thread, NULL, tirasOl, sleepTime);

      /**
      sonlanmış olsa dahi pthread_join ile join işlemine tabi tutulmazlar ise,
      CPU tarafından tekrar schedule edilmeseler de sistemden kullandığı kaynaklar geri verilmez
      */
      pthread_join(thread, &status);

      counter++;
  }

  return 0;
}

// gcc 4.7.2 +
// gcc -std=gnu99 -Wall -g -lpthread -o helloworld_c helloworld_c.c

// For Mint, må me heller bruka:
// gcc -std=gnu99 -Wall -g -o helloworld_c helloworld_c.c -lpthread
// bugger seg dersom me ikkje har -lpthread på slutten på Mint


#include <pthread.h>
#include <stdio.h>

int i = 0;
pthread_mutex_t mtx;

// Note the return type: void*
void* adder(){
    for(int x = 0; x < 1000000; x++){
	pthread_mutex_lock(&mtx);
        i++;
	pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

void* subtraher(){
    for(int x = 0; x < 100000; x++){
	pthread_mutex_lock(&mtx);
        i--;
	pthread_mutex_unlock(&mtx);
    }
    return NULL;
}



int main(){
    pthread_mutex_init(&mtx,NULL);

    pthread_t adder_thr;
    pthread_t subtraher_thr;
    pthread_create(&adder_thr, NULL, adder, NULL);
    pthread_create(&subtraher_thr, NULL, subtraher, NULL);
    for(int x = 0; x < 50; x++){
        printf("%i\n", i);
    }

    pthread_join(adder_thr, NULL);
    pthread_join(subtraher_thr, NULL);
    //pthread_mutex_destroy(&mtx);
    printf("Done: %i\n", i);
    return 0;
    
}



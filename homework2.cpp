#include <iostream>

#include <pthread.h>



static int count = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static pthread_cond_t cv = PTHREAD_COND_INITIALIZER;



void* task(void* arg)

{

	pthread_mutex_lock(&mutex);

	while (count <= 10)

	{

		pthread_cond_wait(&cv, &mutex);

	}

	std::cout << ">10" << std::endl;

	while (count <= 50)

	{

		pthread_cond_wait(&cv, &mutex);

	}

	pthread_mutex_unlock(&mutex);

	return NULL;



}



int main()

{

	pthread_t thread;

	pthread_create(&thread, NULL, task, NULL);

	char c;

	while (std::cin >> c)

	{

		++count;

		if (count > 10)

		{

			pthread_mutex_lock(&mutex);

			pthread_cond_signal(&cv);

			pthread_mutex_unlock(&mutex);



		}

		if (count > 50)

		{

			pthread_mutex_lock(&mutex);

			pthread_cond_signal(&cv);

			pthread_mutex_unlock(&mutex);



		}

	}

	std::cout << "Symbol count - " << count << std::endl;

	pthread_join(thread, NULL);

}

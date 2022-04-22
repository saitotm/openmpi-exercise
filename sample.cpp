#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int rank, proc; //　ランク, 全プロセス数
    int name_length = 10; //　ホスト名の長さ
    int tag = 0;
    int source, dest;
    char message[100];
    MPI_Status status;
    char *name[name_length]; //　ホスト名

    MPI_Init(&argc, &argv); // MPIの初期化
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // ランクの取得
    MPI_Comm_size(MPI_COMM_WORLD, &proc); // 全プロセス数の取得

    if (rank != 0) {
        sprintf(message, "Greetings from process %d", rank);
        dest = 0;
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    } else {
        for (source = 1; source < proc; source++) {
            MPI_Recv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
            printf("%s\n", message);
        }
    }

    MPI_Finalize(); // MPIの終了処理
    return 0;
}

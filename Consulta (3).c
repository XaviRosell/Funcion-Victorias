#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define MAX 1000

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "Error al inicializar la conexión a MySQL\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "usuario", "contrasena", "MultinivelDB", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error al conectar a MySQL: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }




    char username[50];
    printf("Ingrese el nombre de usuario: ");
    scanf("%s", username);

    char query[MAX];
    snprintf(query, MAX, "SELECT COUNT(*) AS PatidasGanadas FROM Partida JOIN Jugador ON Partida.Ganador = Jugador.ID WHERE Jugador.username = '%s';", username);

    if (mysql_query(conn, query) != 0) {
        fprintf(stderr, "Error al realizar la consulta: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("Número de veces que %s ha ganado: ", username);

    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result)) != NULL) {
        printf("%s\n", row[0]);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return 0;
}

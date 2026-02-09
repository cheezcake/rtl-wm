
#include <stdio.h>
#define NULL 0

/* ------------------------------------------------------------ */

char *Rhyme_Read( stream )
    FILE *stream;
{
    char str[128];
    char *result;

    printf( "\f" );
    while ( ( ( result = fgets( str, 128, stream ) ) != NULL ) &&
            ( strlen(str) > 1 ) )
    {
        printf( "%s", str );
    }
    return result;
}


/* ------------------------------------------------------------ */

main()
{
    char *homenv;
    char *result = NULL;
    FILE *stream;
    char *cur;
    char path[256];

    homenv = (char *)getenv("HOME");
    strcpy( path, homenv );
    cur = path + strlen(path);
    while ( *cur != '/' )
        cur--;
    *(cur+1) = '\0';    

    strcat( path, "rtl/extras/rhymes" );

    while ( 1 )
    {
        if ( result == NULL )
            stream = fopen( path, "r" );
        result = Rhyme_Read( stream );
        sleep(6);
        if ( result == NULL )
            fclose( stream );
    }
}

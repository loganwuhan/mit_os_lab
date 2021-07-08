#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int find(char * path, char * name)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return 1;
    }
    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return 1;
    }

    if (st.type != T_DIR)
    {
        fprintf(2, "find: %s is not a directory\n", path);
        return 1;
    }

    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';

    while( read(fd, &de, sizeof(de)) == sizeof(de) )
    {
        if(de.inum == 0)
            continue;
        if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        {
            continue;
        }
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0){
            printf("ls: cannot stat %s\n", buf);
            return 1;
        }
        //fprintf("")
        if(st.type == T_DIR)
        {
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            find(buf, name);
            memset(p, 0, DIRSIZ);
            
        }
        if(strcmp(de.name, name) == 0)
        {
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            fprintf(1, buf);
            //fprintf(1, de.name);
            fprintf(1, "\n");
            memset(p, 0, DIRSIZ);
        }
    }
    return 0;
}


int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        fprintf(2, "usage: find <path> <name>\n");
        exit(1);
    }

    int error = find(argv[1], argv[2]);
    if (error == 1)
        exit(1);

    exit(0);
}
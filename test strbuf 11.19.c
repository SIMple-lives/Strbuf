#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>

struct strbuf 
{
    int len;
    int alloc;
    char *buf;
};

void strbuf_init(struct strbuf *sb,int sizealloc)
{
    sb->alloc=sizealloc;
}

void strbuf_attach(struct strbuf*sb,const char *s,int sizelen,int sizealloc)
{
    sb->buf=(char *)malloc(sizeof(char)*sizealloc);
    strcpy(sb->buf,s); 
    sb->alloc=sizealloc;
    sb->len=sizelen;
}

void strbuf_addstr(struct strbuf *sb,const char *s)
{
    int newlen=strlen(s);
    int size=sb->alloc-sb->len;
    if(newlen>size)
    {
        sb->buf=(char *)realloc(sb->buf,sizeof(char)*(sb->len+newlen+1));
    }
    strcat(sb->buf,s);
    sb->len+=newlen;
}

void strbuf_release(struct strbuf *sb)
{
    free(sb->buf);
}

int main()
{
    struct strbuf sb;
    strbuf_init(&sb,10);
    strbuf_attach(&sb,"xiyou",5,10);
    assert(strcmp(sb.buf,"xiyou")==0);
    strbuf_addstr(&sb,"linux");
    assert(strcmp(sb.buf,"xiyoulinux")==0);
    printf("%s\n",sb.buf);
    strbuf_release(&sb);
    return 0;
}
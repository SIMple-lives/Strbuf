#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

struct strbuf
{
    int len;
    int alloc;
    char *buf;
    /* data */
};

void strbuf_init(struct strbuf*sb,int alloc)
{
    sb->len=0;
    sb->alloc=alloc;
    sb->buf=(char *)malloc(sizeof(char)*alloc);
}

void strbuf_attach(struct strbuf*sb,char *s,int num_len,int num_alloc)
{
    sb->buf=(char *)malloc(sizeof(char)*num_alloc);
    sb->alloc=num_alloc;
    sb->len=num_len;
    strcpy(sb->buf,s);
}

void strbuf_addstr(struct strbuf*sb,char *s)
{   int newlen=strlen(s);
    int size=sb->alloc-sb->len;
    if(newlen>size)
    {
        sb->buf=(char *)realloc(sb->buf,sizeof(char)*(newlen+sb->len));
    }
    strcat(sb->buf,s);
    sb->len+=newlen;
    sb->alloc=sb->len+1;
}
 

void strbuf_release(struct strbuf *sb)
{
    if(sb->buf!=NULL)
    {
    free(sb->buf);
    sb->buf=NULL;
    }
}

void swap_int(int *a,int *b)
{
    *a=*a^*b;
    *b=*a^*b;
    *a=*a^*b;
}

void strbuf_swap(struct strbuf*a,struct strbuf*b)
{
    swap_int(&(a->len),&(b->alloc));
    swap_int(&(a->alloc),&(b->alloc));
    /* char *tmp1=a->buf;
    char *tmp2=b->buf;
    a->buf=(char *)realloc(a->buf,sizeof(char)*a->alloc);
    b->buf=(char *)realloc(b->buf,sizeof(char)*b->alloc);
    a->buf=tmp2;
    b->buf=tmp1; */
    swap_int(&(a->buf),&(b->buf));
}

char *strbuf_detach(struct strbuf*sb,int num_alloc)
{
    char *str=sb->buf;
    sb->alloc=num_alloc;
    sb->buf=(char *)realloc(sb->buf,sizeof(char)*sb->alloc);
    return str;
}

int strbuf_cmp(const struct strbuf *first,const struct strbuf *second)
{
    //int diff=(int *)first->buf-(int *)second->buf;
    return strcmp(first->buf,second->buf);
}

void strbuf_reset(struct strbuf *sb)
{
    free(sb->buf);
    sb->alloc=0;
    sb->len=0;
    sb->buf=NULL;//(char *)realloc(sb->buf,sizeof(char)*0);
}

int main()
{
    struct strbuf sb;
    struct strbuf sc;
    strbuf_init(&sb,10);
    strbuf_attach(&sb,"xiyou",5,10);
    assert(strcmp(sb.buf,"xiyou")==0);
    strbuf_addstr(&sb,"linux");
    assert(strcmp(sb.buf,"xiyoulinux")==0);
    printf("%s\n",sb.buf);
    //strbuf_release(&sb);
    strbuf_init(&sc,10);
    strbuf_attach(&sc,"Welcome ",8,10);
    assert(strcmp(sc.buf,"Welcome ")==0);
    strbuf_addstr(&sc,"to");
    assert(strcmp(sc.buf,"Welcome to")==0);
    printf("%s\n",sc.buf);
    //strbuf_release(&sc);
    strbuf_swap(&sb,&sc);
    printf("%s ",sb.buf);
    printf("%s\n",sc.buf);
    //int sz=0;
    //scanf("%d",&sz);
    char *str=strbuf_detach(&sc,20);
    assert(sc.buf!=NULL);
    printf("%s\n",str);
    int diff=strbuf_cmp(&sb,&sc);
    printf("%d\n",diff);
    strbuf_reset(&sc);
    strbuf_release(&sb);
    strbuf_release(&sc);
    return 0;
}

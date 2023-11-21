#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>



struct strbuf
{
    /* data */
    int len;
    int alloc;
    char *buf;
};

void strbuf_Init(struct strbuf*sb,int alloc)
{
    sb->alloc=alloc;
    sb->buf=(char *)malloc(sizeof(char)*alloc);
    assert(sb->buf!=NULL);
    sb->len=0;
}

void strbuf_Attach(struct strbuf*sb,char *s,int numlen,int numalloc)
{
    if(numalloc<numlen+1)
    {
        sb->buf=(char *)realloc(sb->buf,sizeof(char)*(numlen+1));
        assert(sb->buf!=NULL);
        sb->alloc=numlen+1;
    }
    strcpy(sb->buf,s);
}

void strbuf_Setlen(struct strbuf *sb,int len)
{
    sb->len=len;
}

void strbuf_Release(struct strbuf *sb)
{
    free(sb->buf);
    sb->buf=NULL;
}

void strbuf_Grow(struct strbuf *sb,int len)
{
    if(sb->alloc-sb->len-1<len)
    {
        sb->buf=(char *)realloc(sb->buf,sizeof(char)*(sb->len+len+1));
        assert(sb->buf!=NULL);
        sb->alloc=len+sb->len+1;
    }
}

int main()
{
    struct strbuf sb;
    int n=0;
    printf("初始化结构体，请输入容量大小:\n");
    scanf("%d",&n);
    strbuf_Init(&sb,n);
    char s[6]="xiyou";
    int len=strlen(s);
    strbuf_Setlen(&sb,len);
    strbuf_Attach(&sb,s,len,n);
    int len1=0;
    printf("输入需要的空闲的容量\n");
    scanf("%d",&len1);
    strbuf_Grow(&sb,len1);
    printf("%s\n",sb.buf);
    printf("%d\n",sb.len);
    printf("%d\n",sb.alloc);
    strbuf_Release(&sb);
    return 0;
}

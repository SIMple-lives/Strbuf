void strbuf_ltrim(struct strbuf *sb)
{
    int j=0;
    while(sb->buf[j]==' '||sb->buf[j]=='\t')
    {
        j++;
    }
    sb->len-=j;
    memmove(sb->buf,sb->buf+j,sb->len);
}

void strbuf_rtrim(struct strbuf *sb)
{
    int j=sb->len-1;
    int count=0;
    while(sb->buf[j]==' '||sb->buf[j]=='\t')
    {
        j--;
        count++;
    }
    sb->len-=count;
}

void strbuf_remove(struct strbuf *sb, size_t pos, size_t len)
{
    if(pos+len>sb->len)
    {
        len=sb->len-pos;
    }
    memmove(sb->buf+pos,sb->buf+pos+len,sb->len-pos-len);
    sb->len-=len;
}

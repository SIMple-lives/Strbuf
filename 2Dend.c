ssize_t strbuf_read(struct strbuf *sb, int fd, size_t hint)//要往strbuf的buf中读数据.buf最后一个要变为'\0'。
{
    if (hint == 0)
    {
        hint = 8192;
    }
    if (sb->len + hint >= sb->alloc)
    {
        sb->alloc += hint;
        sb->buf = (char *)realloc(sb->buf, sizeof(char) * sb->alloc);
        assert(sb->buf != NULL);
    }
    char *str = (char *)malloc(sizeof(char) * hint);
    ssize_t ret = read(fd, str, hint);
    if (ret > 0)
    {
        // Ensure that sb->buf is null-terminated before strcat
        sb->buf = (char *)realloc(sb->buf, sb->len + ret + 1);
        assert(sb->buf != NULL);
        memcpy(sb->buf + sb->len, str, ret);
        sb->len += ret;
        sb->buf[sb->len] = '\0';  // Null-terminate the buffer
    }
    free(str);
    return ret;
}

int strbuf_getline(struct strbuf *sb, FILE *fp)
{
    int c=0;
    while((c=fgetc(fp))!=EOF&&c!='\n')
    {
        strbuf_addch(sb,c);
    }
    return 0;
}
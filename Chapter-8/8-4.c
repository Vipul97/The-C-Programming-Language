int fseek(FILE* fp, long offset, int origin)
{
    if (fp->flag & (_EOF | _ERR) != 0)
        return -1;
    if (fp->flag & _READ) {
        fp->ptr = fp->base;
        fp->cnt = 0;
    } else if (fflush(fp) == EOF)
        return EOF;
    return lseek(fp->fd, offset, origin) >= 0 ? 0 : -1;
}

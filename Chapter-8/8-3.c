int _flushbuf(int c, FILE *fp)
{
    int bufsize, flushed;

    if ((fp->flag&(_WRITE|_EOF|_ERR)) != _WRITE)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) {     /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            fp->flag |= ERR;
            return EOF;       /* can't get buffer */
        }
    } else {
        flushed = write(fp->fd, fp->base, fp->ptr - fp->base);
        if (flushed != fp->ptr - fp->base) {
            fp->flag |= _ERR;
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = bufsize - 1;
    return *fp->ptr++ = (char) c;
}

int fflush(FILE *fp)
{
    int flush;

    if ((fp->flag&(_WRITE|_EOF|_ERR)) != _WRITE)
        return EOF;
    flush = _flushbuf(0, fp);
    fp->ptr = fp->base;
    fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    return flush;
}

int fclose(FILE *fp)
{
    int flush_res;

    flush_res = fflush(fp);
    free(fp->base);
    fp->flag &= ~(_READ | _WRITE);
    return flush_res;
}

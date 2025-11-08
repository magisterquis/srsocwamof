/* init.c
 * Start horizontal_aubergine going
 * By J. Stuart McMurray
 * Created 20250906
 * Last Modified 20250906
 */

extern void connect_stdio(void);

static void __attribute__((constructor))
ctor(void)
{
        connect_stdio();
}

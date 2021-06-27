/*
 * Ｇ＿ＬＩＯを用いたグラフィックライブラリの
 * プロトタイプ宣言
 */
void	g_init(void);
void	g_screen(int act,int dsp);
void	g_cls(void);
void	g_palete(int a,int b);
void	g_line(int x0,int y0,int x1,int y1,int col,int func);
void	g_circle(int x,int y,int r,int c);
void	g_paint(int x,int y,int c1,int c2);
void	g_get(int x1,int y1,int x2,int y2,int *dat,int leng);
void	g_put(int x,int y,int *dat,int leng,int mode,int sw,int c1,int c2);

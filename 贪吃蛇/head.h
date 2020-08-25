
#define DEF_SNAKE_LONG 20

// char型二维数组
char g_strGameBack[20][48] = {
										"■■■■■■■■■■■■■■■■■■■■■■■\n",
										"■                                          ■\n",
										"■                                          ■\n",        //方块占两个字节 两个字符位
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■                                          ■\n",
										"■■■■■■■■■■■■■■■■■■■■■■■\n"                                      };

//方向
enum { to_east = 2, to_west = -2, to_north = -1, to_south = 1 };

//蛇数组
int g_arrSnake[DEF_SNAKE_LONG][3] = { 0 };

//蛇长度
int g_nSnakelen = 2;  //初始长度3，尾结点坐标是2

//蛇方向  全局变量 获得的实时方向
int g_nSnakeDir = to_west;

//产生食物
bool g_blProFood = true;

//产生随机坐标
int g_nRow, g_nCol;

//分数
int g_nScore = 0;
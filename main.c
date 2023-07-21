# include "rtklib.h"


int main(void){
    // 初始化
    obs_t *obs = (obs_t *)malloc(sizeof(obs_t));
    nav_t *nav = (nav_t *)malloc(sizeof(nav_t));
    sta_t *sat = (sta_t *)malloc(sizeof(sta_t));
    const char *path = "F:\\work/gpsposition\\explore_rtklib\\data\\MAO000USA_R_20231980000_01D_MN.rnx";

    // rcv=2为固定站，char* opt是一个参数，系统代码system mask（rinex.c -> Line 892），传空值
    int status = readrnx(path, 2, "", NULL, nav, NULL);
    if(status){
        printf("%d", obs->data->rcv);
    }else{
        printf("no data!");
    }
}
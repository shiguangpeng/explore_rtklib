#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rtklib.h"

#include "logme.h"

int main(void) {
    /* 初始化接收观测数据的结构体 */
    obs_t *obs = (obs_t *) malloc(sizeof(obs_t));
    if (!obs) {
        printf("Memory allocation failed!");
        return -1;
    }

    obs->n = 0, obs->nmax = 0;
    obs->data = (obsd_t *) malloc(sizeof(obsd_t));

    /* 初始化接收导航电文的结构体 */
    nav_t *nav = (nav_t *) malloc(sizeof(nav_t));
    if (!nav) {
        printf("Memory allocation failed!");
        free(obs);
        return -1;
    }
    nav->nmax = 0, nav->n = 0;       // 广播星历的条数/数量
    nav->ng = 0, nav->ngmax = 0;     // glonass广播星历的条数/数量
    // nav->ne = 0, nav->nemax = 0;
    nav->ns = 0, nav->nsmax = 0;
    nav->eph = (eph_t *) malloc(sizeof(eph_t));         // GPS/QZS/GAL/BDS/IRN 星历
    nav->geph = (geph_t *) malloc(sizeof(geph_t));      // GLONASS 星历
    nav->seph = (seph_t *) malloc(sizeof(seph_t));      // SBAS 星历

    /* 初始化接收导航电文的结构体 */
    sta_t *sat = (sta_t *) malloc(sizeof(sta_t));       // station parameter type
    if (!sat) {
        printf("Memory allocation failed!");
        free(nav->eph);
        free(nav->geph);
        free(nav->seph);
        free(nav);
        free(obs);
        return -1;
    }

    /* 读文件操作 */
    const char *path = "F:\\work\\gpsposition\\explore_rtklib\\data\\NRMG00NCLN.rnx";

    gtime_t starttime = {.time=202307190000, .sec=0.0};
    gtime_t endtime = {.time=202307190200, .sec=0.0};

    int status = readrnxt(path, 2, starttime, endtime, 0, "-SYS=I", obs, nav,
                          sat); // rcv=2为固定站，char* opt是一个参数，系统代码system mask（rinex.c -> Line 892），传空值
    if (status) {
        logMessage(INFO, strerror(errno));
    } else {
        logMessage(ERRORS, strerror(errno));
        return -1;
    }

    /* 程序结束，释放空间 */
    free(nav->eph);
    free(nav->geph);
    free(nav->seph);
    free(obs->data);
    free(nav);
    free(obs);
    free(sat);

    return 0;
}

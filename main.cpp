//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include "rtklib.h"
//
//#include "logme.h"
//
//int main(void) {
//    /* 初始化接收观测数据的结构体 */
//    obs_t *obs = (obs_t *) malloc(sizeof(obs_t));
//    if (!obs) {
//        printf("Memory allocation failed!");
//        return -1;
//    }
//
//    obs->n = 1000, obs->nmax = 1000;
//    obs->data = (obsd_t *) malloc(sizeof(obsd_t));
//
//    /* 初始化接收导航电文的结构体 */
//    nav_t *nav = (nav_t *) malloc(sizeof(nav_t));
//    if (!nav) {
//        printf("Memory allocation failed!");
//        free(obs);
//        return -1;
//    }
//    nav->nmax = 0, nav->n = 0;       // 广播星历的条数/数量
//    nav->ng = 0, nav->ngmax = 0;     // glonass广播星历的条数/数量
//    nav->ne = 0, nav->nemax = 0;
//    nav->ns = 0, nav->nsmax = 0;
//    nav->eph = (eph_t *) malloc(sizeof(eph_t));         // GPS/QZS/GAL/BDS/IRN 星历
//    nav->geph = (geph_t *) malloc(sizeof(geph_t));      // GLONASS 星历
//    nav->seph = (seph_t *) malloc(sizeof(seph_t));      // SBAS 星历
//
//    /* 初始化接收导航电文的结构体 */
//    sta_t *sat = (sta_t *) malloc(sizeof(sta_t));       // station parameter type
//    if (!sat) {
//        printf("Memory allocation failed!");
//        free(nav->eph);
//        free(nav->geph);
//        free(nav->seph);
//        free(nav);
//        free(obs);
//        return -1;
//    }
//
//    /* 读文件操作 */
//    const char *path = "F:\\work\\gpsposition\\explore_rtklib\\data\\*.rnx";
//    obs_t obs1 = {0};
//    nav_t nav1 = {0};
//    sta_t sta1 = {""};
//
//    // 结果变量
//    sol_t* sol = NULL;
//    char* msg = "";
//    int status = readrnx(path, 2, "", &obs1, &nav1, &sta1); // rcv=2为固定站，char* opt是一个参数，系统代码system mask（rinex.c -> Line 892），传空值
//    if (status) {
//        logMessage(INFO, strerror(errno));
//        // 状态正常时，可以继续操作
//        prcopt_t* opt = NULL;
//        pntpos(obs->data, obs->n, nav, opt, sol, NULL, NULL, msg);
//        printf("%c", *msg);
//    } else {
//        logMessage(ERRORS, "NO DATA!!!");
//        return -1;
//    }
//
//    /* 程序结束，释放空间 */
//    free(nav->eph);
//    free(nav->geph);
//    free(nav->seph);
//    free(obs->data);
//    free(nav);
//    free(obs);
//    free(sat);
//
//    return 0;
//}


#include <stdio.h>
#include <assert.h>
#include <rtklib.h>


static void dumpobs(obs_t *obs) {
    gtime_t time = {0};
    int i;
    char str[64];
    printf("obs : n=%d\n", obs->n);
    for (i = 0; i < obs->n; i++) {
        time2str(obs->data[i].time, str, 3);
        printf("%s : %2d %2d %13.3f %13.3f %13.3f %13.3f  %d %d\n", str, obs->data[i].sat,
               obs->data[i].rcv, obs->data[i].L[0], obs->data[i].L[1],
               obs->data[i].P[0], obs->data[i].P[1], obs->data[i].LLI[0], obs->data[i].LLI[1]);

        assert(1 <= obs->data[i].sat && obs->data[i].sat <= 255);
        assert(timediff(obs->data[i].time, time) >= -DTTOL);

        time = obs->data[i].time;
    }
}

static void dumpnav(nav_t *nav) {
    int i;
    char str[64], s1[64], s2[64];
    printf("nav : n=%d\n", nav->n);
    for (i = 0; i < nav->n; i++) {
        time2str(nav->eph[i].toe, str, 3);
        time2str(nav->eph[i].toc, s1, 0);
        time2str(nav->eph[i].ttr, s2, 0);
        printf("%s : %2d    %s %s %3d %3d %2d\n", str, nav->eph[i].sat, s1, s2,
               nav->eph[i].iode, nav->eph[i].iodc, nav->eph[i].svh);

        //assert(nav->eph[i].iode == (nav->eph[i].iodc & 0xFF));
    }
}

static void dumpsta(sta_t *sta) {
    printf("name    = %s\n", sta->name);
    printf("marker  = %s\n", sta->marker);
    printf("antdes  = %s\n", sta->antdes);
    printf("antsno  = %s\n", sta->antsno);
    printf("rectype = %s\n", sta->rectype);
    printf("recver  = %s\n", sta->recver);
    printf("recsno  = %s\n", sta->recsno);
    printf("antsetup= %d\n", sta->antsetup);
    printf("itrf    = %d\n", sta->itrf);
    printf("deltype = %d\n", sta->deltype);
    printf("pos     = %.3f %.3f %.3f\n", sta->pos[0], sta->pos[1], sta->pos[2]);
    printf("del     = %.3f %.3f %.3f\n", sta->del[0], sta->del[1], sta->del[2]);
    printf("hgt     = %.3f\n", sta->hgt);
}

int main(int argc, char **argv) {

    char file1[] = "F:\\work\\gpsposition\\explore_rtklib\\data\\NRMG00NCLN.rnx";
    char file2[] = "F:\\work\\gpsposition\\explore_rtklib\\data\\NRMG00NCLO.rnx";

    obs_t obs = {0};
    nav_t nav = {0};
    sta_t sta = {""};

    printf("readin rinex file: %s\n", file1);
    printf("================================");

    gtime_t ts = {.time=1689724800, .sec=0.0}, te = {.time=1689732000, .sec=0.0};
    readrnxt(file1, 1, ts, te, 0.0, "", NULL, &nav, NULL);
    dumpnav(&nav);

    gtime_t t0 = {.time=1689724800, .sec=0.0}, t1 = {.time=1689732000, .sec=0.0};
    readrnxt(file2, 1, t0, t1, 1800, "", &obs, NULL, &sta);
    dumpobs(&obs);
    dumpsta(&sta);

    // 填充默认值
    prcopt_t opt = prcopt_default;
    sol_t sol;
    // pntpos
    char msg[100];
    int status = pntpos(obs.data, obs.n, &nav, &opt, &sol, NULL, NULL, msg);
    if (status == 1)//1：OK, 0: error
    {
        double ep[6] = {0};
        time2epoch(sol.time, ep);
        printf("%.0lf,%.0lf,%.0lf,%.0lf,%.0lf,%.0lf,%lf,%lf,%lf,%lf,%lf,%lf,\n", ep[0], ep[1], ep[2], ep[3], ep[4], ep[5],
               sol.rr[0], sol.rr[1], sol.rr[2], sol.rr[3], sol.rr[4], sol.rr[5]);
    }
    else
    {
        printf("status is: %d, msg:%s\n", status, msg);
    }

    free(obs.data);
    return 0;
}
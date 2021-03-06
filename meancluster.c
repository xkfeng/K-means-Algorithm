#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"kmeans.h"

void means_cluster(int clust_num,saved *save)
{
    double center[clust_num][COL];
    double center_backup[clust_num][COL];
    int    counter[clust_num];//how many points of each tag
    int    i,j,k,t,p,flag=1,modified_count;
    double sum,pick_max[clust_num];


    for(i=0; i<clust_num; i++)
    {
        for(j=0; j<COL; j++)
        {
            center[i][j]=save[i].val[j];
            center_backup[i][j]=save[i].val[j];
            // printf("means.c  center=%lf,",center[i][j]);
        }
        printf("\n");

    }

    do
    {
        for(i=0; i<ROW; i++)
        {
            for(j=0; j<clust_num; j++)
            {
                sum=0;
                for(k=0; k<COL; k++)
                {
                    sum+=pow(center[j][k]-data[i].val[k],2);
                }
                pick_max[j]=sqrt(sum);
            }
            for(p=0,t=1; t<clust_num; t++)
            {
                if(pick_max[p]>pick_max[t])
                {
                    p=t;
                }
            }

            data[i].tag=p;
        }


        //initial center to zero
        for(i=0; i<clust_num; i++)
        {
            for(j=0; j<COL; j++)
            {
                center[i][j]=0;
            }
            counter[i]=0;
        }
        //recalculate the central points
        for(i=0; i<ROW; i++)
        {
            for(j=0; j<COL; j++)
            {
                center[data[i].tag][j]+=data[i].val[j];
            }
            counter[data[i].tag]++;//count the numbers of each tag
        }

        for(i=0; i<clust_num; i++)
        {
            for(j=0; j<COL; j++)
            {
                center[i][j]/=counter[i];
                //printf(" center=%f,center_backup=%f",center[i][j],center_backup[i][j]);
            }
        }//end


        // if each element in center_backup equals to center,
        // it means the center point is no longer change,
        // then finish the while loop
        modified_count=0;
        for(i=0; i<clust_num; i++)
        {
            for(j=0; j<COL; j++)
            {
                if(center[i][j]!=center_backup[i][j])
                {
                    center_backup[i][j]=center[i][j];
                    modified_count++;
                }
            }
        }
        if(modified_count==0)
        {
            flag=0;
        }
    }
    while(flag);

/*
    //debug info
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            //printf("ROW=%d,COL=%d,center[%d][%d]=%f ",ROW,COL,i,j,center[i][j]);
            printf("data[%d].val %f,tag=%d,",i,data[i].val[j],data[i].tag);
        }
        printf("\n");
        //printf(",count=%d\n\n",counter[i]);
    }
    //end debuf info
    */

    free(save);
}


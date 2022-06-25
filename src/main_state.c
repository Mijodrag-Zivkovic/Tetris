#include <main_state.h>
#include <glad/glad.h>
#include <math.h>
#include <time.h>
#include <rafgl.h>
static rafgl_raster_t doge;
static rafgl_raster_t raster;
static rafgl_texture_t texture;
static rafgl_raster_t raster2;

static int raster_width = 0, raster_height = 0;
static int duzina_stranice = 50;
int matrica[11][12];
int oblici[50];
int xkoordinata, ykoordinata;
int xkoordinate[4];
int ykoordinate[4];
int xmat[4], ymat[4];
int xpomeraj, ypomeraj;
int shape;
int length;
int lerp(int l, int r, float s)
{
    return l + (r - l) * s;
}
rafgl_pixel_rgb_t lerp_pixel(rafgl_pixel_rgb_t l, rafgl_pixel_rgb_t r, float s)
{
    rafgl_pixel_rgb_t result;
    /* svaka komponenta ponaosob interpolirana */
    result.r = lerp(l.r, r.r, s);
    result.g = lerp(l.g, r.g, s);
    result.b = lerp(l.b, r.b, s);
    result.a = lerp(l.a, r.a, s);
    return result;
}
// iscrtava ivice terena zajedno sa mrezom
void iscrtaj_pozadinu()
{
    int x=0,y;
    for(y=0;y<raster_height;y++)
    {
        for(x=0;x<raster_width;x++)
        {
            if(y<500)
            {
                if(x<50 || x> 549)
                {
                    pixel_at_m(raster, x, y).rgba = rafgl_RGB(0, 0, 0);
                }
                else
                    pixel_at_m(raster, x, y).rgba = rafgl_RGB(255, 255, 255);
            }
            else
            {
                    pixel_at_m(raster, x, y).rgba = rafgl_RGB(0, 0, 0);
            }
            if(x%50==0 || y%50==0)
            pixel_at_m(raster, x, y).rgba = rafgl_RGB(0, 0, 255);
        }
    }

}
void iscrtaj_teren()
{
    int pamti=0;
    int i,j;int x,y;
    printf("teren\n");
    srand(time(NULL));
    int num;
    num = rand();
    num = num % 3 + 1;
    rafgl_pixel_rgb_t left_colour, right_colour;
    rafgl_pixel_rgb_t upper_left_colour, lower_left_colour, upper_right_colour, lower_right_colour;
    int c1,c2,c3;
    c1=rand();c1=c1%256;
    c2=rand();c2=c2%256;
    c3=rand();c3=c3%256;
    left_colour.rgba = rafgl_RGB(rand()%256, rand()%256, rand()%256);
    right_colour.rgba = rafgl_RGB(rand()%256, rand()%256, rand()%256);

    upper_left_colour.rgba = rafgl_RGB(rand()%256, rand()%256, rand()%256);
    upper_right_colour.rgba = rafgl_RGB(rand()%256, rand()%256, rand()%256);
    lower_left_colour.rgba = rafgl_RGB(rand()%256, rand()%256, rand()%256);
    lower_right_colour.rgba = rafgl_RGB(rand()%256, rand()%256, rand()%256);

    for(j=0;j<10;j++)
    {
        printf("\n");
        for(i=1;i<11;i++)
        {
            //x_pomocno = i*50;
            printf("%d",matrica[j][i]);
            if(matrica[j][i]==1)
            {
                int m2=0;
                for(y=j*50;y<j*50+50;y++)
                {
                    int m=0;
                    for(x=i*50;x<i*50+50;x++)
                    {
                        //prvi case - lerping celog terena
                        //float x_pomocno2 = (1.0f * x )/ 550;
                        //pixel_at_m(raster, x, y) = lerp_pixel(left_colour, right_colour, x_pomocno2);


                        //drugi case - lerping svakog kvadratica ponaosob
                        //float x_pomocno = (1.0f * m)/50;
                        //pixel_at_m(raster, x, y) = lerp_pixel(left_colour, right_colour, x_pomocno);
                       // m++;


                        //treci case - noise
                        //c1=rand();c1=c1%256;
                       // c2=rand();c2=c2%256;
                       // c3=rand();c3=c3%256;
                       // pixel_at_m(raster, x, y).rgba = rafgl_RGB(c1, c2, c3);


                       // cetvrti case - bilinear gradient (lerping i po y) celog terena
                       // rafgl_pixel_rgb_t tmp_left, tmp_right;
                       // float y_normalized = 1.0f * y / 500;
                       // tmp_left = lerp_pixel(upper_left_colour, lower_left_colour, y_normalized);
                       // tmp_right = lerp_pixel(upper_right_colour, lower_right_colour, y_normalized);
                       //float x_pomocno2 = (1.0f * x )/ 550;
                        //pixel_at_m(raster, x, y) = lerp_pixel(tmp_left, tmp_right, x_pomocno2);


                        //peti case - bilinear gradient jednog kvadratica
                          rafgl_pixel_rgb_t tmp_left, tmp_right;
                          float y_normalized = 1.0f * m2 / 50;
                          tmp_left = lerp_pixel(upper_left_colour, lower_left_colour, y_normalized);
                          tmp_right = lerp_pixel(upper_right_colour, lower_right_colour, y_normalized);
                          float x_pomocno2 = (1.0f * m)/ 50;
                          pixel_at_m(raster, x, y) = lerp_pixel(tmp_left, tmp_right, x_pomocno2);
                          m++;
                        //pixel_at_m(raster, x, y).rgba = rafgl_RGB(0, 0, 0);
                    }
                    m2++;
                }
            }
        }
    }
}
// arbitrary gradient

//////////////////////////////////////////////////////////////
// iscrtava kvadrat
void iscrtaj_oblik(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{

    xkoordinate[0]=x1;
    ykoordinate[0]=y1;
    xkoordinate[1]=x2;
    ykoordinate[1]=y2;
    xkoordinate[2]=x3;
    ykoordinate[2]=y3;
    xkoordinate[3]=x4;
    ykoordinate[3]=y4;
    xmat[0] = xkoordinate[0]/50;
    ymat[0] = ykoordinate[0]/50;
    xmat[1] = xkoordinate[1]/50;
    ymat[1] = ykoordinate[1]/50;
    xmat[2] = xkoordinate[2]/50;
    ymat[2] = ykoordinate[2]/50;
    xmat[3] = xkoordinate[3]/50;
    ymat[3] = ykoordinate[3]/50;
    //printf("%d %d\n",xmat,ymat);
    int c1,c2,c3;
    srand(time(NULL));
    c1 = rand();
    c1 = c1 % 256;
    c2 = rand();
    c2 = c2 % 256;
    c3 = rand();
    c3 = c3 % 256;
    int i,j;
    for(j=y1;j<y1+50;j++)
    {
        for(i=x1;i<x1+50;i++)
        {
            pixel_at_m(raster, i, j).rgba = rafgl_RGB(c1, c2, c3);
        }
    }
    for(j=y2;j<y2+50;j++)
    {
        for(i=x2;i<x2+50;i++)
        {
            pixel_at_m(raster, i, j).rgba = rafgl_RGB(c1, c2, c3);
        }
    }
    for(j=y3;j<y3+50;j++)
    {
        for(i=x3;i<x3+50;i++)
        {
            pixel_at_m(raster, i, j).rgba = rafgl_RGB(c1, c2, c3);
        }
    }
    for(j=y4;j<y4+50;j++)
    {
        for(i=x4;i<x4+50;i++)
        {
            pixel_at_m(raster, i, j).rgba = rafgl_RGB(c1, c2, c3);
        }
    }

}
// generise broj od 1-5, na osnovu cega se iscrtava neki od oblika gore, smesta u niz redni broj oblika
void generisi_oblik()
{
    xpomeraj=1;
    ypomeraj=0;
    int num;
    srand(time(NULL));
    num = rand();
    num = num % 5 + 1;
    switch(num)
    {
    case 1:
        iscrtaj_oblik(50,0, 100, 0, 50, 50, 100, 50);
        shape=1;
        length=1;
        break;
    case 2:
        iscrtaj_oblik(50,0, 50, 50, 50, 100, 50, 150);
        shape=2;
        length=3;
        break;
    case 3:
        iscrtaj_oblik(50,0, 50, 50, 50, 100, 100,100);
        shape=3;
        length=2;
        break;
    case 4:
        iscrtaj_oblik(50,0, 100, 0, 100, 50, 150, 50);
        shape=4;
        length=2;
        break;
    case 5:
        iscrtaj_oblik(100,0, 50,50, 100,50, 150,50);
        shape=5;
        length=2;
        break;
    default:
        break;
    }
}
void main_state_init(GLFWwindow *window, void *args)
{
    /* inicijalizacija */
    /* raster init nam nije potreban ako radimo load from image */
    rafgl_raster_load_from_image(&doge, "res/images/doge.png");
    raster_width = 600;
    raster_height = 550;

    rafgl_raster_init(&raster, raster_width, raster_height);
    int i,j;
    for(j=0;j<11;j++)
    {
        printf("\n");
        for(i=0;i<12;i++)
        {
            if(i==0||i==11||j==10)
                matrica[j][i]=1;
            else
            matrica[j][i]=0;

            printf("%d",matrica[j][i]);
        }

    }
    iscrtaj_pozadinu();
   // generisi_oblik();
   // iscrtaj_oblik(50,0, 100, 0, 50, 50, 100, 50);
   //iscrtaj_oblik(50,0, 50, 50, 50, 100, 50, 150);
   //iscrtaj_oblik(50,0, 50, 50, 50, 100, 100,100);
   //iscrtaj_oblik(50,0, 100, 0, 100, 50, 150, 50);
   //iscrtaj_oblik(100,0, 50,50, 100,50, 150,50);
   generisi_oblik();

}

int pressed, location = 0;
float selector = 0;

void pomeri_teren()
{
    int i,j;
    int brojac;
    for(j=9;j>=0;j--)
    {
        printf("%d",j);
        brojac = 0;
        for(i=1;i<11;i++)
        {
            if(matrica[j][i]==1)
            {
                brojac++;
            }
        }
        if(brojac==10)
        {
            pomeri_matricu(j);
            iscrtaj_teren();
            j++;
        }

    }
}
void pomeri_matricu(int m)
{
    int i,j;
    for(j=m;j>0;j--)
    {
        for(i=1;i<11;i++)
        {
            matrica[j][i]=matrica[j-1][i];
        }
    }
    for(i=1;i<11;i++)
    {
        matrica[0][i] = 0;
    }
}
void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args)
{

    /* hendluj input */
    if(game_data->is_lmb_down && game_data->is_rmb_down)
    {
        pressed = 1;
        location = rafgl_clampi(game_data->mouse_pos_y, 0, raster_height - 1);
        selector = 1.0f * location / raster_height;
    }
    else
    {
        pressed = 0;
    }

    if(game_data->keys_down[RAFGL_KEY_S])
    {
        if(matrica[ymat[0]+1][xmat[0]]==0 && matrica[ymat[1]+1][xmat[1]]==0 && matrica[ymat[2]+1][xmat[2]]==0 && matrica[ymat[3]+1][xmat[3]]==0)
        {
            iscrtaj_pozadinu();
            iscrtaj_teren();
            iscrtaj_oblik(xkoordinate[0],ykoordinate[0]+50,xkoordinate[1],ykoordinate[1]+50,xkoordinate[2],ykoordinate[2]+50,xkoordinate[3],ykoordinate[3]+50);
            delay();
            ypomeraj++;
        }
        else
        {
            matrica[ymat[0]][xmat[0]]=1;
            matrica[ymat[1]][xmat[1]]=1;
            matrica[ymat[2]][xmat[2]]=1;
            matrica[ymat[3]][xmat[3]]=1;
            int i,j;
            for(j=0;j<11;j++)
            {
                printf("\n");
                for(i=0;i<12;i++)
                {
                    printf("%d",matrica[j][i]);
                }
            }
            pomeri_teren();
            //iscrtaj_oblik(50,0, 100, 0, 50, 50, 100, 50);
            generisi_oblik();
        }

    }
    if(game_data->keys_down[RAFGL_KEY_A])
    {
        if(matrica[ymat[0]][xmat[0]-1]==0 && matrica[ymat[1]][xmat[1]-1]==0 && matrica[ymat[2]][xmat[2]-1]==0 && matrica[ymat[3]][xmat[3]-1]==0)
        {
            iscrtaj_pozadinu();
            iscrtaj_teren();
            iscrtaj_oblik(xkoordinate[0]-50,ykoordinate[0],xkoordinate[1]-50,ykoordinate[1],xkoordinate[2]-50,ykoordinate[2],xkoordinate[3]-50,ykoordinate[3]);
            delay();
            xpomeraj--;
        }
    }
    if(game_data->keys_down[RAFGL_KEY_D])
    {
        if(matrica[ymat[0]][xmat[0]+1]==0 && matrica[ymat[1]][xmat[1]+1]==0 && matrica[ymat[2]][xmat[2]+1]==0 && matrica[ymat[3]][xmat[3]+1]==0)
        {
            iscrtaj_pozadinu();
            iscrtaj_teren();
            iscrtaj_oblik(xkoordinate[0]+50,ykoordinate[0],xkoordinate[1]+50,ykoordinate[1],xkoordinate[2]+50,ykoordinate[2],xkoordinate[3]+50,ykoordinate[3]);
            delay();
            xpomeraj++;
        }
    }
    if(game_data->keys_down[RAFGL_KEY_R])
    {
        printf("pomerajx %d\n", xpomeraj);
        printf("ypomeraj %d\n", ypomeraj);
        int i,j;
        int xmatpriv[4],ymatpriv[4];
        int privniz[4];
        for(j=0;j<4;j++)
        {
            xmatpriv[j] = xmat[j]-xpomeraj;
            ymatpriv[j] = ymat[j]-ypomeraj;
            privniz[j] = ymat[j]-ypomeraj;
        }
        for(j=0;j<4;j++)
        {
            ymatpriv[j] = xmatpriv[j];
            xmatpriv[j] = length - privniz[j];
        }
        printf("\n");
        for(j=0;j<4;j++)
        {
            xmat[j]=xmatpriv[j]+xpomeraj;
            ymat[j]=ymatpriv[j]+ypomeraj;
            printf("%d ",xmat[j]);
            printf("%d ",ymat[j]);
            printf("\n");
        }
        iscrtaj_pozadinu();
        iscrtaj_teren();
        iscrtaj_oblik(xmat[0]*50,ymat[0]*50, xmat[1]*50,ymat[1]*50,xmat[2]*50,ymat[2]*50,xmat[3]*50,ymat[3]*50);
        delay();
    }



    /* update-uj teksturu*/


        rafgl_texture_load_from_raster(&texture, &raster);



}


void main_state_render(GLFWwindow *window, void *args)
{
    /* prikazi teksturu */
    rafgl_texture_show(&texture);
}


void main_state_cleanup(GLFWwindow *window, void *args)
{
    rafgl_raster_cleanup(&raster);
    rafgl_texture_cleanup(&texture);

}


void delay()
{
    int c, d;

   for (c = 1; c <= 32767/3; c++)
       for (d = 1; d <= 32767/3; d++)
       {}
        ;
}

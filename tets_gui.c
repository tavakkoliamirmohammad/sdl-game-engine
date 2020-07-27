//#include <stdio.h>
//#include "C:\Program Files\mingw-w64\x86_64-8.1.0-win32-seh-rt_v6-rev0\mingw64\include\SDL2\SDL.h"
//
//#define PI  3.14159
//#define SCR_WDT  640
//#define SCR_HGT  480
//
//const int SCR_CEN_X = SCR_WDT / 2;
//const int SCR_CEN_Y = SCR_HGT / 2;
//
//int main(int arcg, char *a[]) {
//    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
//        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
//        return EXIT_FAILURE;
//    }
//    SDL_Init ( SDL_INIT_VIDEO );
//    SDL_Window *window = SDL_CreateWindow ( "Drawing a Circle",       SDL_WINDOWPOS_UNDEFINED,
//                                            SDL_WINDOWPOS_UNDEFINED, SCR_WDT, SCR_HGT, SDL_WINDOW_OPENGL );
//    SDL_Delay(200000);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}
////
//////int _tmain(int argc, _TCHAR* argv[])
//////{
//////    AVFormatContext    *pFormatCtx;
//////    int                i, videoindex;
//////    AVCodecContext    *pCodecCtx;
//////    AVCodec            *pCodec;
//////    char filepath[]="nwn.mp4";
//////    av_register_all();
//////    avformat_network_init();
//////    pFormatCtx = avformat_alloc_context();
//////    if(avformat_open_input(&pFormatCtx,filepath,NULL,NULL)!=0){
//////        printf("Unable to open file \n");
//////        return -1;
//////    }
//////    if(av_find_stream_info(pFormatCtx)<0)
//////    {
//////        printf("Couldn't find stream information.\n");
//////        return -1;
//////    }
//////    videoindex=-1;
//////    for(i=0; i<pFormatCtx->nb_streams; i++)
//////        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
//////        {
//////            videoindex=i;
//////            break;
//////        }
//////    if(videoindex==-1)
//////    {
//////        printf("Didn't find a video stream.\n");
//////        return -1;
//////    }
//////    pCodecCtx=pFormatCtx->streams[videoindex]->codec;
//////    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
//////    if(pCodec==NULL)
//////    {
//////        printf("Codec not found.\n");
//////        return -1;
//////    }
//////    if(avcodec_open(pCodecCtx, pCodec)<0)
//////    {
//////        printf("Could not open codec.\n");
//////        return -1;
//////    }
//////    AVFrame    *pFrame,*pFrameYUV;
//////    pFrame=avcodec_alloc_frame();
//////    pFrameYUV=avcodec_alloc_frame();
//////    uint8_t *out_buffer;
//////    out_buffer=new uint8_t[avpicture_get_size(PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height)];
//////    avpicture_fill((AVPicture *)pFrameYUV, out_buffer, PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);
////////------------SDL----------------
//////    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
//////        printf( "Could not initialize SDL - %s\n", SDL_GetError());
//////        exit(1);
//////    }
//////    SDL_Surface *screen;
//////    screen = SDL_SetVideoMode(pCodecCtx->width, pCodecCtx->height, 0, 0);
//////    if(!screen) {  printf("SDL: could not set video mode - exiting\n");
//////        exit(1);
//////    }
//////    SDL_Overlay *bmp;
//////    bmp = SDL_CreateYUVOverlay(pCodecCtx->width, pCodecCtx->height,SDL_YV12_OVERLAY, screen);
//////    SDL_Rect rect;
////////---------------
//////    int ret, got_picture;
//////    static struct SwsContext *img_convert_ctx;
//////    int y_size = pCodecCtx->width * pCodecCtx->height;
//////
//////    AVPacket *packet=(AVPacket *)malloc(sizeof(AVPacket));
//////    av_new_packet(packet, y_size);
//////    //The output information on position
//////    printf("File information -----------------------------------------\n");
//////    av_dump_format(pFormatCtx,0,filepath,0);
//////    printf("-------------------------------------------------\n");
//////    //------------------------------
//////    while(av_read_frame(pFormatCtx, packet)>=0)
//////    {
//////        if(packet->stream_index==videoindex)
//////        {
//////            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
//////            if(ret <0)
//////            {
//////                printf("Decoding error \n");
//////                return -1;
//////            }
//////            if(got_picture)
//////            {
//////                img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
//////                sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
//////
//////                SDL_LockYUVOverlay(bmp);
//////                bmp->pixels[0]=pFrameYUV->data[0];
//////                bmp->pixels[2]=pFrameYUV->data[1];
//////                bmp->pixels[1]=pFrameYUV->data[2];
//////                bmp->pitches[0]=pFrameYUV->linesize[0];
//////                bmp->pitches[2]=pFrameYUV->linesize[1];
//////                bmp->pitches[1]=pFrameYUV->linesize[2];
//////                SDL_UnlockYUVOverlay(bmp);
//////                rect.x = 0;
//////                rect.y = 0;
//////                rect.w = pCodecCtx->width;
//////                rect.h = pCodecCtx->height;
//////                SDL_DisplayYUVOverlay(bmp, &rect);
//////                //Delay 40ms
//////                SDL_Delay(40);
//////            }
//////        }
//////        av_free_packet(packet);
//////    }
//////    delete[] out_buffer;
//////    av_free(pFrameYUV);
//////    avcodec_close(pCodecCtx);
//////    avformat_close_input(&pFormatCtx);
//////
//////    return 0;
//////}
/* tinyplay.c
**
** Copyright 2011, The Android Open Source Project
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of The Android Open Source Project nor the names of
**       its contributors may be used to endorse or promote products derived
**       from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY The Android Open Source Project ``AS IS'' AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL The Android Open Source Project BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
** CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
** LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
** OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
** DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#include "asoundlib.h"

#define SAMPLE_RATE 44100
#define CHANNEL 2
#define BUFFER_SIZE (1024)

unsigned short buffer[BUFFER_SIZE];


void generate_sine(int freq, int volume)
{
    int i = 0;
    for (i = 0; i < BUFFER_SIZE / CHANNEL; i++) {
        double x = i * 2 * 3.1415926 / (SAMPLE_RATE / freq);
        
        unsigned short data = (unsigned short) (volume * sin(x) + 32768);
        if (CHANNEL == 1) {
            buffer[i] = data;
        } else {
            buffer[2 * i] = data;
            buffer[2 * i + 1] = data;
        }
    }
}


void pcm_init_config(struct pcm_config* config)
{
    unsigned int channels = 2;
    unsigned int rate = SAMPLE_RATE;
    unsigned int bits = 16;
    unsigned int period_size = 128;
    unsigned int period_count = 2;
    
    config->channels = channels;
    config->rate = rate;
    config->period_size = period_size;
    config->period_count = period_count;
    config->format = PCM_FORMAT_S16_LE;
    config->start_threshold = 0;
    config->stop_threshold = 0;
    config->silence_threshold = 0;   
}

struct pcm* get_pcm_out()
{
    unsigned int card = 0;
    unsigned int device = 0;
    
    struct pcm_config config;
    struct pcm *pcm_out;

    pcm_init_config(&config);
    
    pcm_out = pcm_open(card, device, PCM_OUT, &config);
   	if (!pcm_out || !pcm_is_ready(pcm_out)) {
        printf("Unable to open PCM device %u (%s)\n",
                device, pcm_get_error(pcm_out));
        return NULL;
    }
    
    return pcm_out;
}

struct pcm* get_pcm_in()
{
    unsigned int card = 0;
    unsigned int device = 0;
    
    struct pcm_config config;
    struct pcm *pcm_in;

    pcm_init_config(&config);
    
    pcm_in = pcm_open(card, device, PCM_IN, &config);
   	if (!pcm_in || !pcm_is_ready(pcm_in)) {
        printf("Unable to open PCM device %u (%s)\n",
                device, pcm_get_error(pcm_in));
        return NULL;
    }
    
    return pcm_in;
}

int play()
{
    struct pcm *pcm_out = get_pcm_out();
    
    generate_sine(2000, 10000);
    
    while (1) {
        if (!pcm_write(pcm_out, buffer, BUFFER_SIZE)) {
            //printf("sucess in to out: %d\n", BUFFER_SIZE);	
        } else {
            printf("failed\n");
            break;
        }
    }
    
    return 0;
}

void loopback()
{
    struct pcm *pcm_out = get_pcm_out();
    struct pcm *pcm_in = get_pcm_in();
    unsigned char buff[128];
    
    if (!pcm_out || !pcm_in)
        return;
    
    printf("buffer size:%d %d\n", pcm_get_buffer_size(pcm_out), pcm_get_buffer_size(pcm_in));
    
    while(1) {
        int ret = pcm_read(pcm_in, buff, sizeof(buff)); 
        if (!ret) {
       		if (!pcm_write(pcm_out, buff, sizeof(buff))) {
       			//printf("sucess in to out: %d\n", sizeof(buff));	
       		} else {
       			break;
       		}
       	} else {
            break;
        }
    }
    
    printf("exit!\n");
}

int main()
{
    //play();
    loopback();
    return 0;
}


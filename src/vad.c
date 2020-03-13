#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "vad.h"
#include "pav_analysis.h"

const float FRAME_TIME = 10.0F; /* in ms. */
const float fm = 16000;
int Ninit = 0;
float ten = 10;

/* 
 * As the output state is only ST_VOICE, ST_SILENCE, or ST_UNDEF,
 * only this labels are needed. You need to add all labels, in case
 * you want to print the internal state in string format
 */

const char *state_str[] = {
    "UNDEF", "S", "V", "MS", "MV", "INIT"};

const char *state2str(VAD_STATE st)
{
  return state_str[st];
}

/* Define a datatype with interesting features */
typedef struct
{
  float zcr;
  float p;
  float am;
} Features;

/* 
 * TODO: Delete and use your own features!
 */

Features compute_features(const float *x, int N)
{
  Features feat;
  feat.p = compute_power(x, N);
  feat.zcr = compute_zcr(x, N, fm);
  feat.am = compute_am(x, N);

  /*
   * Input: x[i] : i=0 .... N-1 
   * Ouput: computed features
   */
  /* 
   * DELETE and include a call to your own functions
   *
   * For the moment, compute random value between 0 and 1 
   */

  return feat;
}

/* 
 * TODO: Init the values of vad_data
 */

VAD_DATA *vad_open(float rate)
{
  VAD_DATA *vad_data = malloc(sizeof(VAD_DATA));
  vad_data->state = ST_INIT;
  vad_data->k0 = -100;
  vad_data->k1 = 0;
  vad_data->k2 = 0;
  vad_data->state_time = 0;
  vad_data->last_feature = 0;
  vad_data->sampling_rate = rate;
  vad_data->frame_length = rate * FRAME_TIME * 1e-3;
  return vad_data;
}

VAD_STATE vad_close(VAD_DATA *vad_data)
{
  /* 
   * TODO: decide what to do with the last undecided frames
   */

  VAD_STATE state = vad_data->state;
  free(vad_data);
  return state;
}

unsigned int vad_frame_size(VAD_DATA *vad_data)
{
  return vad_data->frame_length;
}

/* 
 * TODO: Implement the Voice Activity Detection 
 * using a Finite State Automata
 */
float pot = 0;
int N = 0;
float des = 0;
VAD_STATE vad(VAD_DATA *vad_data, float *x)
{
  N++;
  /* 
   * TODO: You can change this, using your own features,
   * program finite state automaton, define conditions, etc.
   */

  Features f = compute_features(x, vad_data->frame_length);

  switch (vad_data->state)
  {
  case ST_INIT:
    if (vad_data->last_feature < f.p)
    {
      vad_data->k0 = f.p;
      if (f.p > vad_data->last_feature + 5)
      {
        vad_data->k0 = vad_data->last_feature;
        vad_data->k1 = vad_data->k0 + (f.p - vad_data->last_feature) - 2;
        vad_data->k2 = vad_data->k1 + 5;
        vad_data->state = ST_SILENCE;
      }
    }

    break;

  case ST_SILENCE:
    Ninit = 0;
    if (f.p > vad_data->k1)
    {

      vad_data->state = ST_MaybeVOICE;
    }

    break;

  case ST_MaybeVOICE:
    vad_data->state_time = vad_data->state_time + FRAME_TIME;
    if (f.p > vad_data->k1 && vad_data->state_time > 50)
    { /* Sponemos que el tiempo maximo de una pausa breve es de 50 ms*/
      vad_data->state = ST_SILENCE;
      vad_data->state_time = 0;
    }
    else if (f.p > vad_data->k2)
    {
      vad_data->state = ST_VOICE;
      vad_data->state_time = 0;
    }

    break;

  case ST_VOICE:
    if (f.p < vad_data->k2)
    {
      vad_data->state = ST_MaybeSILENCE;
    }

    break;

  case ST_MaybeSILENCE:
    vad_data->state_time = vad_data->state_time + FRAME_TIME;
    if (f.p < vad_data->k2 && vad_data->state_time > 50)
    { /* Sponemos que el tiempo maximo de una pausa breve es de 50 ms*/
      vad_data->state = ST_VOICE;
      vad_data->state_time = 0;
    }
    else if (f.p < vad_data->k1)
    {
      vad_data->state = ST_SILENCE;
      vad_data->state_time = 0;
    }
    break;

  case ST_UNDEF:
    break;
  }
  vad_data->last_feature = f.p;
  /*printf("%f %f %f\n", vad_data->k0, vad_data->k1, vad_data->k2);*/
  if (vad_data->state == ST_SILENCE || vad_data->state == ST_VOICE)
    return vad_data->state;
  else
    return ST_UNDEF;
}

void vad_show_state(const VAD_DATA *vad_data, FILE *out)
{
  fprintf(out, "%d\t%f\n", vad_data->state, vad_data->last_feature);
}

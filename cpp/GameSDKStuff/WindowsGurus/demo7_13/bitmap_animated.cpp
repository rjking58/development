
#typedef unsigned int   UINT;
#typedef unsigned short USHORT;

struct Animation_Cels
{
   LPDIRECTDRAWSURFACE7 *cels;
   UINT                 cel_cnt;
   UINT                 *cel_sequence;
   USHORT               cel_sequence_cnt;
};

AnimationCels *cels;
   
struct Actor
{
   Actor(UINT           x,
         UINT           y,
         UINT           x_velo,
         UINT           y_velo,
         USHORT         anim_delay,
         AnimationCels  *cels )
      : m_x(x),
        m_y(y),
        m_x_velo(x_velo),
        m_y_velo(y_velo),
        m_anim_delay(anim_delay),
        m_cels(cels),
        m_current_cel(0)
   {
   }

   UINT           m_x;
   UINT           m_y;
   UINT           m_x_velo;
   UINT           m_y_velo;
   USHORT         m_anim_delay;
   USHORT         m_current_cel;
   AnimationCels  *m_cels; 
};


// 1. Animation cells (sharable) (actual cells, animation sequence)
// 2. Actor Tracking 2d (x,y; x_velo; y_velo; cell animation offset (current animation sequence); state mechanism (for complex actors)
// 
// 

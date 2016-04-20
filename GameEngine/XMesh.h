#pragma once

#include"XStructures.h"


class MyXModel
{
   public:
      MyXModel();
      ~MyXModel() { }

      void SetDevice(LPDIRECT3DDEVICE9 device)
      {
         m_device = device;
      }

      bool LoadXFile(char *file);
      void Shutdown();

      void GetBoundingSphere(D3DXVECTOR3 *center, float *radius)
      {
         if(center) *center = m_center;
         if(radius) *radius = m_radius;
      }

      void Update(float time, const D3DXMATRIX *matWorld);

      void Render();

      void SetAnimation(unsigned int index);
      void NextAnimation();

      unsigned int GetCurrentAnimation() { return m_currentAni; }
      unsigned int GetTotalAnimations() { return m_numAnimations; }

      float GetAnimationSpeed() { return m_speed; }
      void IncreaseAnimationSpeed(float amt) { m_speed += amt; }
      void DecreaseAnimationSeep(float amt)
      {
         if(m_speed > 0.1f) m_speed -= amt;
      }

      float GetTransitionSpeed() { return m_transition; }
      void DecreaseTransitionSpeed(float amt) { m_transition += amt; }
      void IncreaseTransitionSeep(float amt)
      {
         if(m_transition > 0.1f) m_transition -= amt;
      }


   private:
      void SetupMatrices(myD3DFrameEx *inFrame,
                         LPD3DXMATRIX parentMatrix);
      void UpdateMatrices(const D3DXFRAME *inFrame, const D3DXMATRIX *parentMatrix);
      void DrawFrame(LPD3DXFRAME frame);


   private:
      // D3D Device
      LPDIRECT3DDEVICE9 m_device;

      // Root frame and animation controller.
      LPD3DXFRAME m_root;
      LPD3DXANIMATIONCONTROLLER m_animControl;

      // Bones.
      D3DXMATRIX *m_boneMatrices;
      unsigned int m_maxBones;

      // Current mesh container.
      myD3DContainerEx *m_currentContainer;

      // Bounding sphere.
      D3DXVECTOR3 m_center;
      float m_radius;

      // Animation variables.
      unsigned int m_currentAni;
      unsigned int m_numAnimations;
      unsigned long m_currentTrack;
      float m_speed;
      float m_currentTime;
      float m_transition;
};

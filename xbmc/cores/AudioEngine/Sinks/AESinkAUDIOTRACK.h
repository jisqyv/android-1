#pragma once
/*
 *      Copyright (C) 2010-2012 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "Interfaces/AESink.h"
#include "Utils/AEDeviceInfo.h"

typedef void* ATW_ctx;
class AERingBuffer;

class CAESinkAUDIOTRACK : public CThread, public IAESink
{
public:
  virtual const char *GetName() { return "AUDIOTRACK"; }

  CAESinkAUDIOTRACK();
  virtual ~CAESinkAUDIOTRACK();

  virtual bool Initialize(AEAudioFormat &format, std::string &device);
  virtual void Deinitialize();
  virtual bool IsCompatible(const AEAudioFormat format, const std::string device);

  virtual double       GetDelay        ();
  virtual double       GetCacheTime    ();
  virtual double       GetCacheTotal   ();
  virtual unsigned int AddPackets      (uint8_t *data, unsigned int frames);
  virtual void         Drain           ();
  static void          EnumerateDevicesEx(AEDeviceInfoList &list);

private:
  virtual void OnStartup();
  virtual void OnExit();
  virtual void Process();

  void                 ProbeSupportedSampleRates();

  static CAEDeviceInfo m_info;
  AEAudioFormat      m_format;
  AERingBuffer      *m_sinkbuffer;
  double             m_sinkbuffer_sec;
  double             m_sinkbuffer_sec_per_byte;

  CEvent             m_inited;
  volatile int       m_init_frames;
  volatile bool      m_draining;
  double             m_audiotrackbuffer_sec;
  double             m_audiotrackbuffer_sec_per_byte;
  double             m_audiotracklatency_sec;
};

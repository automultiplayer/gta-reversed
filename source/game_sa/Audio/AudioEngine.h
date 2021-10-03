#pragma once

#include "AEFrontendAudioEntity.h"
#include "AEScriptAudioEntity.h"
#include "AERadioTrackManager.h"
#include "AECollisionAudioEntity.h"
#include "AEGlobalWeaponAudioEntity.h"
#include "AEPedlessSpeechAudioEntity.h"

class CEntity;
class CColPoint;
class CVector;

struct tBeatInfo {
    char  f0[12];
    char  fC[148];
    int32 m_beatInfoPresent;
    char  fA4[8];
};
VALIDATE_SIZE(tBeatInfo, 0xAC);

class CAudioEngine {
public:
    bool                        field_0;
    bool                        field_1;
    RadioStationId              m_nCurrentRadioStationId;
    RadioStationId              m_nSavedRadioStationId;
    int32                       m_nBackgroundAudioChannel;
    tBeatInfo                   m_BeatInfo;
    CAEFrontendAudioEntity      m_FrontendAE;
    CAEScriptAudioEntity        m_ScriptAE;
    CAECollisionAudioEntity     m_CollisionAE;
    CAEGlobalWeaponAudioEntity* m_GlobalWeaponAE;
    CAEPedlessSpeechAudioEntity m_PedlessSpeechAE;
    CAEDoorAudioEntity          m_DoorAE;

public:
    static void InjectHooks();

    CAudioEngine() = default;  // 0x507670
    ~CAudioEngine() = default; // 0x506CD0

    bool Initialise();
    void InitialisePostLoading();
    void Shutdown();

    void Reset();
    void ResetStatistics();
    void ResetSoundEffects();

    static void Restart();

    bool IsLoadingTuneActive();
    static bool IsRadioOn();
    bool IsRadioRetuneInProgress();
    bool IsVehicleRadioActive();
    static bool IsCutsceneTrackActive();
    bool IsBeatInfoPresent();
    static bool IsAmbienceTrackActive();
    static bool IsAmbienceRadioActive();
    bool IsMissionAudioSampleFinished(uint8 sampleId);

    void SetMusicMasterVolume(int8);
    void SetEffectsMasterVolume(int8);
    void SetMusicFaderScalingFactor(float);
    void SetEffectsFaderScalingFactor(float);
    void ServiceLoadingTune(float);
    void SetStreamFaderScalingFactor(float);
    void SetNonStreamFaderScalingFactor(float);

    static void EnableEffectsLoading();
    static void DisableEffectsLoading();

    void ReportCollision(CEntity* entity1, CEntity* entity2, uint8 surface1, uint8 surface2, CVector& point, CVector* normal, float fCollisionImpact1, float fCollisionImpact2, bool playOnlyOneShotCollisionSound, bool unknown);
    void ReportBulletHit(CEntity* entity, uint8 a3, CVector& posn, float a5);
    void ReportObjectDestruction(CEntity* entity);
    void ReportGlassCollisionEvent(eAudioEvents, CVector&);
    void ReportWaterSplash(CVector posn, float volume);
    void ReportWaterSplash(CPhysical* physical, float volume, bool forcePlaySplashSound);
    void ReportWeaponEvent(int32_t audioEvent, eWeaponType weaponType, CPhysical* physical);
    void ReportDoorMovement(CPhysical* pPhysical);
    void ReportMissionAudioEvent(uint16 eventId, CVector& posn);
    void ReportMissionAudioEvent(uint16 eventId, CObject* object);
    void ReportMissionAudioEvent(uint16 eventId, CPed* ped);
    void ReportMissionAudioEvent(uint16 eventId, CVehicle* vehicle);
    void ReportMissionAudioEvent(uint16 eventId, CPhysical* physical, float a3, float a4);
    void ReportFrontendAudioEvent(eAudioEvents eventId, float volumeChange, float speed);

    void InitialiseRadioStationID(RadioStationId id);
    void StartRadio(tVehicleAudioSettings* settings);
    void StartRadio(int8, int8);
    void StopRadio(tVehicleAudioSettings* settings, bool bDuringPause);
    void SetRadioAutoRetuneOnOff(bool);
    void SetBassEnhanceOnOff(bool enable);
    void SetRadioBassSetting(int8);
    bool HasRadioRetuneJustStarted();
    char* GetRadioStationName(RadioStationId id);
    void GetRadioStationNameKey(RadioStationId id, char* outStr);
    int32* GetRadioStationListenTimes();
    void DisplayRadioStationName();
    RadioStationId GetCurrentRadioStationID();
    void PlayRadioAnnouncement(uint32);
    void RetuneRadio(int8);

    void PreloadCutsceneTrack(int16 trackId, bool wait);
    static void PlayPreloadedCutsceneTrack();
    void StopCutsceneTrack(bool);
    int8 GetCutsceneTrackStatus();
    int8 GetBeatTrackStatus();

    void PlayPreloadedBeatTrack(bool a2);
    void StopBeatTrack();
    tBeatInfo* GetBeatInfo();
    void PauseBeatTrack(bool pause);

    void PreloadBeatTrack(int16 trackId);
    void StopAmbienceTrack(bool a1);
    static bool DoesAmbienceTrackOverrideRadio();
    void PreloadMissionAudio(uint8 sampleId, int32 a3);
    int8 GetMissionAudioLoadingStatus(uint8 sampleId);
    void PlayLoadedMissionAudio(uint8 sampleId);
    int32 GetMissionAudioEvent(uint8 sampleId);
    CVector* GetMissionAudioPosition(uint8 sampleId);
    void ClearMissionAudio(uint8 sampleId);
    void SetMissionAudioPosition(uint8 sampleId, CVector& posn);

    CVector* AttachMissionAudioToPed(uint8 sampleId, CPed* ped);
    CVector* AttachMissionAudioToObject(uint8 sampleId, CObject* object);
    CVector* AttachMissionAudioToPhysical(uint8 sampleId, CPhysical* physical);

    void SayPedless(int32 a1, int16 a2, CEntity* entity, uint32 playOffset, float a5, uint8 a6, uint8 a7, uint8 a8);

    void EnablePoliceScanner();
    void DisablePoliceScanner(uint8, uint8);

    void StopPoliceScanner(uint8);
    void StartLoadingTune();

    static void PauseAllSounds();
    static void ResumeAllSounds();

    void Service();

#ifdef ANDROID
    void Save();
    void Load();
#endif
};

VALIDATE_SIZE(CAudioEngine, 0x1FD8);
VALIDATE_OFFSET(CAudioEngine, m_FrontendAE, 0x0B4);
VALIDATE_OFFSET(CAudioEngine, m_ScriptAE, 0x2A0);
VALIDATE_OFFSET(CAudioEngine, m_CollisionAE, 0x4BC);
VALIDATE_OFFSET(CAudioEngine, m_GlobalWeaponAE, 0x1E34);
VALIDATE_OFFSET(CAudioEngine, m_PedlessSpeechAE, 0x1E38);
VALIDATE_OFFSET(CAudioEngine, m_DoorAE, 0x1F50);

extern CAudioEngine& AudioEngine;
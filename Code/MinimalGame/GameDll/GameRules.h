#ifndef __GAMERULES_H__
#define __GAMERULES_H__

#if _MSC_VER > 1000
# pragma once
#endif

#include <IGameRulesSystem.h>
#include <IViewSystem.h>
#include <IConsole.h>

struct IGameObject;
struct IActorSystem;

class CActor;

class CGameRules 
	:	public CGameObjectExtensionHelper<CGameRules, IGameRules, 64>
{
public:
	CGameRules();
	virtual ~CGameRules();

	//IGameObjectExtension
	virtual bool Init( IGameObject * pGameObject );
	virtual void PostInit( IGameObject * pGameObject );
	virtual void InitClient(int channelId) {}
	virtual void PostInitClient(int channelId) {}
	virtual bool ReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) { return false; }
	virtual void PostReloadExtension( IGameObject * pGameObject, const SEntitySpawnParams &params ) {}
	virtual bool GetEntityPoolSignature( TSerialize signature ) { return false; }
	virtual void Release() { delete this; }
	virtual void FullSerialize(TSerialize ser) {}
	virtual bool NetSerialize( TSerialize ser, EEntityAspects aspect, uint8 profile, int flags );
	virtual void PostSerialize() {}
	virtual void SerializeSpawnInfo( TSerialize ser ) {}
	virtual ISerializableInfoPtr GetSpawnInfo() {return 0;}
	virtual void Update( SEntityUpdateContext& ctx, int updateSlot );
	virtual void HandleEvent(const SGameObjectEvent&) {}
	virtual void ProcessEvent( SEntityEvent& );
	virtual void SetChannelId(uint16 id) {};
	virtual void SetAuthority( bool auth ) {}
	virtual void PostUpdate( float frameTime ) {}
	virtual void PostRemoteSpawn() {};
	virtual void GetMemoryUsage(ICrySizer * s) const;
	//~IGameObjectExtension

	// IGameRules
	virtual bool ShouldKeepClient(int channelId, EDisconnectionCause cause, const char *desc) const;

	virtual void PrecacheLevel() {}
	virtual void PrecacheLevelResource(const char* resourceName, EGameResourceType resourceType) {};

	virtual XmlNodeRef FindPrecachedXmlFile(const char *sFilename) { return 0; }

	virtual void OnConnect(struct INetChannel *pNetChannel) {}
	virtual void OnDisconnect(EDisconnectionCause cause, const char *desc) {}

	virtual bool OnClientConnect(int channelId, bool isReset);
	virtual void OnClientDisconnect(int channelId, EDisconnectionCause cause, const char *desc, bool keepClient);
	virtual bool OnClientEnteredGame(int channelId, bool isReset);

	virtual void OnEntitySpawn(IEntity *pEntity) {}
	virtual void OnEntityRemoved(IEntity *pEntity) {}
	virtual void OnEntityReused(IEntity *pEntity, SEntitySpawnParams &params, EntityId prevId) {}
	
	virtual void OnItemDropped(EntityId itemId, EntityId actorId) {}
	virtual void OnItemPickedUp(EntityId itemId, EntityId actorId) {}

	virtual void SendTextMessage(ETextMessageType type, const char *msg, uint32 to=eRMI_ToAllClients, int channelId=-1,
		const char *p0=0, const char *p1=0, const char *p2=0, const char *p3=0) {}
	virtual void SendChatMessage(EChatMessageType type, EntityId sourceId, EntityId targetId, const char *msg) {}
	virtual bool CanReceiveChatMessage(EChatMessageType type, EntityId sourceId, EntityId targetId) const { return false; }

	virtual void ClientHit(const HitInfo &hitInfo) {}
	virtual void ServerHit(const HitInfo &hitInfo) {}

	virtual int GetHitTypeId(const uint32 crc) const { return 0; }
	virtual int GetHitTypeId(const char *type) const { return 0; }
	virtual const char *GetHitType(int id) const { return ""; }

	virtual void OnVehicleDestroyed(EntityId id) {}
	virtual void OnVehicleSubmerged(EntityId id, float ratio) {}

	virtual bool CanEnterVehicle(EntityId playerId) { return false; }

	virtual void CreateEntityRespawnData(EntityId entityId) {}
	virtual bool HasEntityRespawnData(EntityId entityId) const { return false; }
	virtual void ScheduleEntityRespawn(EntityId entityId, bool unique, float timer) {}
	virtual void AbortEntityRespawn(EntityId entityId, bool destroyData) {}

	virtual void ScheduleEntityRemoval(EntityId entityId, float timer, bool visibility) {}
	virtual void AbortEntityRemoval(EntityId entityId) {}

	virtual void AddHitListener(IHitListener* pHitListener) {}
	virtual void RemoveHitListener(IHitListener* pHitListener) {}

	virtual bool OnCollision(const SGameCollision& event) { return true; }
	virtual void OnCollision_NotifyAI( const EventPhys * pEvent ) {}

	virtual void ShowStatus();

	virtual bool IsTimeLimited() const { return false; }
	virtual float GetRemainingGameTime() const { return 0; }
	virtual void SetRemainingGameTime(float seconds) {}

	virtual void ClearAllMigratingPlayers(void) {}
	virtual EntityId SetChannelForMigratingPlayer(const char* name, uint16 channelID) { return 0; }
	virtual void StoreMigratingPlayer(IActor* pActor) {}

	virtual bool IsClientFriendlyProjectile(const EntityId projectileId, const EntityId targetEntityId) { return false; }
	
	virtual const char *GetTeamName(int teamId) const override { return ""; }
	// ~IGameRules

	IActor *GetActorByChannelId(int channelId) const;

	IActor *GetActorByEntityId(EntityId entityId) const;
	const char *GetActorName(IActor *pActor);

public:
protected:
	bool                m_timeOfDayInitialized;
};

#endif //__GAMERULES_H__

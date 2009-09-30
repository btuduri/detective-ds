#ifndef __CFX_H__
#define __CFX_H__

#define MAX_FX		32

enum FxType
{
	FXTYPE_FADE,
	FXTYPE_FADE_RAMP,
	FXTYPE_TEXT_SCROLLER,
	FXTYPE_COLOUR,
	FXTYPE_PARTICLES
};

enum FxMode
{
	FXMODE_NORMAL,
	FXMODE_BLACK_IN,
	FXMODE_BLACK_OUT,
	FXMODE_WHITE_IN,
	FXMODE_WHITE_OUT,
	FXMODE_ALPHA_IN,
	FXMODE_ALPHA_OUT,
	FXMODE_PULSE,
	FXMODE_RAIN
};

class CFxManager;

class CFx
{
public:
	CFx(FxType fxType, CFxManager* fxManager);
	~CFx();
	
	virtual void Initialize();
	virtual void Shutdown();
	virtual void Reset();
	virtual void UpdateVBlank();
	virtual void UpdateHBlank();
	
	FxType GetFxType() const { return m_fxType; };
	FxMode GetFxMode() const { return m_fxMode; };
	bool Enabled() const { return m_enabled; };
	CFxManager* FxManager() const { return m_fxManager; };
	
	void SetEnabled(FxMode fxMode, bool enabled) { m_fxMode = fxMode; m_enabled = enabled; (enabled ? Initialize() : Shutdown()); }
	void SetFxMode(FxMode fxMode) { m_fxMode = fxMode; }

private:

	FxType m_fxType;
	FxMode m_fxMode;
	
	CFxManager* m_fxManager;
	bool m_enabled;
};

#endif
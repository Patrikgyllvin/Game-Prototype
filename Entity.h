#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity
{
private:
	const unsigned int UEID;

	int maxHealth;
	int health;

	std::string texLoc;
	bool texChanged;

public:
	Entity( unsigned int UEID, bool invX, bool invY );
	virtual ~Entity();
       
	unsigned int getUEID();

	void tick( long dt );

	/// Returns an int containing position for texture. Do NOT use the update function to increment / decrement texPos!
    virtual int getTexturePos();
	virtual int getColor();

	bool getTexChanged();
	const char* getTexLocation();

	void setPosX( double x );
	void setPosY( double y );

	double getPosX();
	double getPosY();

	void setRotX( double rotX );
	void setRotZ( double rotZ );

	double getRotX();
	double getRotZ();

	bool getInvX();
	bool getInvY();

protected:
	double x, y;
	double rotX, rotZ;

	bool invX, invY;

	virtual void onUpdate( long dt ) = 0;
	virtual int getMaxHealth();

	void changeTextureLoc( const char* textureLocation );
};

#endif

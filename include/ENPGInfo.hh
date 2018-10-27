#include <G4VUserEventInformation.hh>
#include <G4String.hh>

class ENPGInfo: public G4VUserEventInformation
{
	public:
	ENPGInfo(G4String str);
	~ENPGInfo();

	public:
	virtual void Print() const;

	private:
	G4String str;
};


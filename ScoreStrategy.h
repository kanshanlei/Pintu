#include <stdio.h>
#include <ScoreData.h>
class ScoreStrategy 
{
private:
	int _continues;//不需要提示的关卡数
public:
	ScoreStrategy();
	virtual void execute(ScoreData* score);
};

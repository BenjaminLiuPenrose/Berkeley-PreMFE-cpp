// Assignment5Q2.cpp : 


#include <iostream>
#include <fstream>
#include <vector>
#include "agents.h"
using namespace std;

void runSimulation(Dealer& dealer, const string& outputFileName) {
	vector<vector<double>> simResults;

	dealer.runSimulation(10000, 100, simResults);

	ofstream outFile;
	outFile.open(outputFileName);
	reportOnPrices(simResults, outFile);
	outFile.close();

}

int main()
{
	Dealer dealer(0.01);

	dealer.addAgent("noise", 1, 1, 0, 0);

	// run the simulation with just a noise trader
	runSimulation(dealer, "just_noise.csv");

	// now, add in value and momentum traders
	dealer.addAgent("value", 0.0261500211448778, 0.244261248416166, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0961920547796019, 0.152980887147034, 0.5, 0.5);
	dealer.addAgent("value", 0.0381898432025544, 0.12741859007716, 0.5, 0.5);
	dealer.addAgent("value", 0.0346118547413692, 0.136824425274402, 0.5, 0.5);
	dealer.addAgent("value", 0.0796595387345472, 0.231874468450134, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0523326861793412, 0.160590834998324, 0.5, 0.5);
	dealer.addAgent("value", 0.0215865787300108, 0.134312209979864, 0.5, 0.5);
	dealer.addAgent("value", 0.0129595090145375, 0.130836710545228, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0975939654267774, 0.110057245575946, 0.5, 0.5);
	dealer.addAgent("value", 0.0356670972756593, 0.227429976581063, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0732508538410833, 0.155447955093191, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0129062854245041, 0.119192435083158, 0.5, 0.5);
	dealer.addAgent("value", 0.0310416573503293, 0.158447327500148, 0.5, 0.5);
	dealer.addAgent("value", 0.0530986634181033, 0.135376210600777, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0398346315615858, 0.157529938266824, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0636565071802407, 0.156011234572934, 0.5, 0.5);
	dealer.addAgent("value", 0.0332614375770669, 0.16036887748351, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0368265531311917, 0.122672862066686, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0862351808401664, 0.181765804811392, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0304486845267019, 0.141776050853096, 0.5, 0.5);
	dealer.addAgent("value", 0.0735704292840399, 0.129069869493419, 0.5, 0.5);
	dealer.addAgent("value", 0.0628267556110595, 0.206078199172512, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0282701954449677, 0.140744242481775, 0.5, 0.5);
	dealer.addAgent("value", 0.0313456718381551, 0.203993284367177, 0.5, 0.5);
	dealer.addAgent("value", 0.0332808249436945, 0.1945705379708, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0314190084225387, 0.169675105893295, 0.5, 0.5);
	dealer.addAgent("value", 0.0454716459157306, 0.224542604028778, 0.5, 0.5);
	dealer.addAgent("value", 0.00611311048458112, 0.152652674481661, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0730053622273029, 0.169854959576576, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0691133246041062, 0.181425041943845, 0.5, 0.5);
	dealer.addAgent("value", 0.0711532548013639, 0.128738434028054, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0511054322567552, 0.189559864351869, 0.5, 0.5);
	dealer.addAgent("momentum", 0.000961868911757324, 0.114963709580087, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0152741623177094, 0.128857372935565, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0374875036279415, 0.155891273492895, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0610874487792963, 0.159459553941794, 0.5, 0.5);
	dealer.addAgent("momentum", 0.046852789673705, 0.112641459831907, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0247070552202434, 0.118154536665072, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0830930246469522, 0.134676158382391, 0.5, 0.5);
	dealer.addAgent("value", 0.0629992201226304, 0.137923180868916, 0.5, 0.5);
	dealer.addAgent("value", 0.0898563601569092, 0.214447920766512, 0.5, 0.5);
	dealer.addAgent("value", 0.0728006288661847, 0.132528345341341, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0173065365563583, 0.101974294950856, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0863779336032764, 0.169576976987058, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0825048117539193, 0.117991206046849, 0.5, 0.5);
	dealer.addAgent("value", 0.0819117009101519, 0.243473472989999, 0.5, 0.5);
	dealer.addAgent("value", 0.0701243791437966, 0.148341991526658, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0576656258677131, 0.192897988698316, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0154131356870642, 0.184499078007401, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0805087574813482, 0.180589031661784, 0.5, 0.5);
	dealer.addAgent("momentum", 0.00237524544774469, 0.168693950227072, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0693374980670098, 0.138994821182009, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0322184365138544, 0.198587457378279, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0712941220209762, 0.133351433992024, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0252467256094667, 0.183489892133655, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0945040734365176, 0.142129166295496, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0636521498525221, 0.198678412746423, 0.5, 0.5);
	dealer.addAgent("value", 0.0509581796057148, 0.178403986072911, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0363971051854844, 0.102130276920012, 0.5, 0.5);
	dealer.addAgent("value", 0.0760415933761997, 0.19129610643846, 0.5, 0.5);
	dealer.addAgent("value", 0.0325032321127876, 0.161588628146798, 0.5, 0.5);
	dealer.addAgent("value", 0.0548009685711384, 0.142618501459934, 0.5, 0.5);
	dealer.addAgent("value", 0.0773398963079263, 0.211075351039139, 0.5, 0.5);
	dealer.addAgent("value", 0.0431729247751307, 0.21837314540447, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0568696967809301, 0.150780893741932, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0299114757096819, 0.168267205580705, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0507777456523843, 0.192473910174433, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0378134439676029, 0.134724265867962, 0.5, 0.5);
	dealer.addAgent("momentum", 0.057223409843251, 0.105677130675967, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0190203217536565, 0.101404984824177, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0918259111282111, 0.127434240676664, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0464799537610711, 0.135199472533208, 0.5, 0.5);
	dealer.addAgent("value", 0.0921010390629481, 0.223024786170485, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0763355750005589, 0.137447468132117, 0.5, 0.5);
	dealer.addAgent("value", 0.0495647772301201, 0.230895634932307, 0.5, 0.5);
	dealer.addAgent("value", 0.00160009909458342, 0.134147274503895, 0.5, 0.5);
	dealer.addAgent("value", 0.0180248598377321, 0.239990119914797, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0469926159464055, 0.115010964734559, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0410535799528257, 0.15072083826645, 0.5, 0.5);
	dealer.addAgent("momentum", 0.070630737306435, 0.121842526033696, 0.5, 0.5);
	dealer.addAgent("value", 0.0392301148547525, 0.194377791120276, 0.5, 0.5);
	dealer.addAgent("value", 0.0575829532187343, 0.201976117953181, 0.5, 0.5);
	dealer.addAgent("value", 0.0613490976862658, 0.229145776335193, 0.5, 0.5);
	dealer.addAgent("value", 0.0878399310225534, 0.168931342542944, 0.5, 0.5);
	dealer.addAgent("value", 0.0892696495604895, 0.218430269464128, 0.5, 0.5);
	dealer.addAgent("value", 0.0316666817397162, 0.219280141023422, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0589004422760969, 0.124029516382631, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0613727281716166, 0.109442513959274, 0.5, 0.5);
	dealer.addAgent("value", 0.0218243223684466, 0.166391405788349, 0.5, 0.5);
	dealer.addAgent("momentum", 0.069606196230966, 0.108658048107988, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0962471607545308, 0.183404773078095, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0266159594045608, 0.154221591130282, 0.5, 0.5);
	dealer.addAgent("value", 0.0681377567656234, 0.245945800745886, 0.5, 0.5);
	dealer.addAgent("value", 0.0412913402490125, 0.148131701195722, 0.5, 0.5);
	dealer.addAgent("value", 0.0549347318324971, 0.139856170938623, 0.5, 0.5);
	dealer.addAgent("momentum", 0.066949077753121, 0.153951428682241, 0.5, 0.5);
	dealer.addAgent("value", 0.0601442199102424, 0.218968437297747, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0146463749891788, 0.107935538126027, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0561906401572795, 0.111724718883681, 0.5, 0.5);
	dealer.addAgent("momentum", 0.0916470648223749, 0.193939999597042, 0.5, 0.5);

	runSimulation(dealer, "value_momentum.csv");
}


/*
www.mhc-pathway.net/smm
Original file by Bjoern Peters.

This software is provided 'as-is', without any express or implied 
warranty. In no event will the authors be held liable for any 
damages arising from the use of this software.

Permission is granted to anyone to use this software for any 
purpose, including commercial applications, and to alter it and 
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must 
not claim that you wrote the original software. If you use this 
software in a product, an acknowledgment in the product documentation 
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source 
distribution.
*/
#pragma once
#include "SMMSet.h"
//#include "SeqMatrix.h"

// Calculates the optimal x given a CSMMSet and  lambda 

enum	LAMBDA_GROUPING	{ONE_COVAR, GROUP_COVAR, ONE_LAMBDA, GROUP_LAMBDA};

struct InitParamSolve
{
	double lambda_min;
	double lambda_max;
	double precision;
	unsigned max_iterations;
	LAMBDA_GROUPING lambda_grouping;
	unsigned group_size;
	CNumMat inverse_covar;

	InitParamSolve()
	{
		lambda_min = 0.0001;
		lambda_max = 10000000;
		precision = 0.0001;
		max_iterations = 1000;
		lambda_grouping = GROUP_COVAR;
		group_size = 20;
		// Matrix are taken from Background/InverseCovariance.txt. Code Snippet was generatd with MatrixToCode.py 
		CNumMat m(20,20);
		m(0,0) = 6.9154674374466705; m(0,1) = -3.071610319860098; m(0,2) = 0.13449848471925185; m(0,3) = -0.7411222293076409; m(0,4) = -0.28051210866626164; m(0,5) = -1.5176480966502766; m(0,6) = 0.9656697766532927; m(0,7) = 0.6064733343512947; m(0,8) = -0.028207337619220632; m(0,9) = 0.7984194482100955; m(0,10) = -0.9140737416130899; m(0,11) = 1.3644491988664085; m(0,12) = -1.1655819810620596; m(0,13) = 1.3950776002855854; m(0,14) = -0.8730336229158846; m(0,15) = -1.133042907802999; m(0,16) = -1.2982500738664329; m(0,17) = -3.0012170674801575; m(0,18) = 3.171270388142828; m(0,19) = -0.32702618183130516; 
		m(1,0) = -3.071610319860098; m(1,1) = 13.750336183875827; m(1,2) = -0.0645985601046683; m(1,3) = -2.7538215554325856; m(1,4) = -1.0219779038972987; m(1,5) = -1.9860785099854195; m(1,6) = -1.6636092737781039; m(1,7) = -1.034087402039568; m(1,8) = 0.3691800179820517; m(1,9) = -0.07662857857899164; m(1,10) = 0.9665987399437106; m(1,11) = -1.2342530780518657; m(1,12) = -0.2166829869417958; m(1,13) = 0.724222283881546; m(1,14) = 0.225912610815319; m(1,15) = 0.15601500304851568; m(1,16) = 0.7762269203999075; m(1,17) = 1.1238489162860679; m(1,18) = -4.491300862131707; m(1,19) = 0.5223083545691525; 
		m(2,0) = 0.13449848471925185; m(2,1) = -0.0645985601046683; m(2,2) = 9.920779763040741; m(2,3) = -6.148444474508619; m(2,4) = 0.24302131209452876; m(2,5) = -0.14716308956490037; m(2,6) = 0.009778563615818806; m(2,7) = -0.1239527738130414; m(2,8) = -0.1872222674271362; m(2,9) = 0.9666292155369451; m(2,10) = -0.8107175587224749; m(2,11) = -1.5578097714390555; m(2,12) = -1.4508136306428177; m(2,13) = 1.756845257210287; m(2,14) = -0.014460697272117372; m(2,15) = 0.36626896693032396; m(2,16) = -1.9742749695115842; m(2,17) = 0.9329900095630002; m(2,18) = -0.9794964566164313; m(2,19) = 0.1281426769119465; 
		m(3,0) = -0.7411222293076409; m(3,1) = -2.7538215554325856; m(3,2) = -6.148444474508619; m(3,3) = 13.440155933463775; m(3,4) = -0.9774392637370108; m(3,5) = 0.20154553570595568; m(3,6) = -0.038563751672343896; m(3,7) = 0.046885854686767384; m(3,8) = 0.6003319689232267; m(3,9) = -1.8917189170300919; m(3,10) = 1.0438451361908212; m(3,11) = 0.2232009544308219; m(3,12) = 0.26577320569953433; m(3,13) = -3.849378381177347; m(3,14) = 0.5517126415557532; m(3,15) = 0.00650683192043492; m(3,16) = 0.6521703895101867; m(3,17) = -0.2814422133508827; m(3,18) = 1.0755483805816946; m(3,19) = -0.4257460464524473; 
		m(4,0) = -0.28051210866626164; m(4,1) = -1.0219779038972987; m(4,2) = 0.24302131209452876; m(4,3) = -0.9774392637370108; m(4,4) = 7.38531387941884; m(4,5) = -1.8109039579797206; m(4,6) = -0.7659368659993191; m(4,7) = -1.043525191554031; m(4,8) = 1.1378975337048143; m(4,9) = -2.4918918261069765; m(4,10) = -0.17368410414739704; m(4,11) = 0.02818697383157301; m(4,12) = 0.25670781668264986; m(4,13) = 2.5458420114891607; m(4,14) = -0.5486053649680269; m(4,15) = 0.4917817293663597; m(4,16) = 0.8189317184179818; m(4,17) = 0.4617931031901016; m(4,18) = -1.4775196206150571; m(4,19) = -1.77747987052491; 
		m(5,0) = -1.5176480966502766; m(5,1) = -1.9860785099854195; m(5,2) = -0.14716308956490037; m(5,3) = 0.20154553570595568; m(5,4) = -1.8109039579797206; m(5,5) = 10.36313910211247; m(5,6) = 0.6038794001804475; m(5,7) = -0.3934820600267858; m(5,8) = -1.3084778357235858; m(5,9) = 0.886669833202246; m(5,10) = 0.11331352521010055; m(5,11) = -0.7910784859543236; m(5,12) = -0.4084637721729303; m(5,13) = -1.7918083624070256; m(5,14) = 0.8238072669516932; m(5,15) = -2.5766847148194616; m(5,16) = 0.14082153503785938; m(5,17) = 0.538159075122896; m(5,18) = 0.5017223428129025; m(5,19) = -0.44126873105214004; 
		m(6,0) = 0.9656697766532927; m(6,1) = -1.6636092737781039; m(6,2) = 0.009778563615818806; m(6,3) = -0.038563751672343896; m(6,4) = -0.7659368659993191; m(6,5) = 0.6038794001804475; m(6,6) = 7.927248464026457; m(6,7) = 0.9025265412853194; m(6,8) = -1.4158176195077554; m(6,9) = -0.3329794741093235; m(6,10) = -0.7037578010068068; m(6,11) = -1.6954277505398494; m(6,12) = 0.13616344280998272; m(6,13) = 0.5224593489232829; m(6,14) = -1.6482910320851194; m(6,15) = -0.7935789576914996; m(6,16) = -1.3267173787123192; m(6,17) = 0.987828419194378; m(6,18) = 0.23611172686753357; m(6,19) = -0.9069857784540717; 
		m(7,0) = 0.6064733343512947; m(7,1) = -1.034087402039568; m(7,2) = -0.1239527738130414; m(7,3) = 0.046885854686767384; m(7,4) = -1.043525191554031; m(7,5) = -0.3934820600267858; m(7,6) = 0.9025265412853194; m(7,7) = 6.876969301108016; m(7,8) = -0.6882229712083282; m(7,9) = -1.4414345579854326; m(7,10) = -2.1305674958720493; m(7,11) = 1.1093672090468547; m(7,12) = -0.1637605700083815; m(7,13) = 0.7730202493033265; m(7,14) = 0.4755144452040677; m(7,15) = -0.2794715244282062; m(7,16) = 0.8044036043399664; m(7,17) = -3.4692907160962365; m(7,18) = -0.2246396468256504; m(7,19) = 0.3972743705320977; 
		m(8,0) = -0.028207337619220632; m(8,1) = 0.3691800179820517; m(8,2) = -0.1872222674271362; m(8,3) = 0.6003319689232267; m(8,4) = 1.1378975337048143; m(8,5) = -1.3084778357235858; m(8,6) = -1.4158176195077554; m(8,7) = -0.6882229712083282; m(8,8) = 8.205636507420976; m(8,9) = -2.1057454480881437; m(8,10) = 0.29459500647959214; m(8,11) = -0.24573511829681077; m(8,12) = -0.050618202875799996; m(8,13) = 1.5495212869358013; m(8,14) = -4.656229128444837; m(8,15) = -0.33337186178847716; m(8,16) = 0.04019787851854289; m(8,17) = -0.2174957912971931; m(8,18) = 0.26108739797930125; m(8,19) = -0.22130401566702068; 
		m(9,0) = 0.7984194482100955; m(9,1) = -0.07662857857899164; m(9,2) = 0.9666292155369451; m(9,3) = -1.8917189170300919; m(9,4) = -2.4918918261069765; m(9,5) = 0.886669833202246; m(9,6) = -0.3329794741093235; m(9,7) = -1.4414345579854326; m(9,8) = -2.1057454480881437; m(9,9) = 12.874098900854213; m(9,10) = -4.573174877360428; m(9,11) = -0.550187212165625; m(9,12) = 0.16635671326089554; m(9,13) = -3.058211311077955; m(9,14) = 1.5817727477406398; m(9,15) = 2.218594753049418; m(9,16) = -0.2775230283900285; m(9,17) = -3.7157530121819082; m(9,18) = 1.7939562592872373; m(9,19) = 0.2287503719332163; 
		m(10,0) = -0.9140737416130899; m(10,1) = 0.9665987399437106; m(10,2) = -0.8107175587224749; m(10,3) = 1.0438451361908212; m(10,4) = -0.17368410414739704; m(10,5) = 0.11331352521010055; m(10,6) = -0.7037578010068068; m(10,7) = -2.1305674958720493; m(10,8) = 0.29459500647959214; m(10,9) = -4.573174877360428; m(10,10) = 10.640812699203579; m(10,11) = -1.2481594086620302; m(10,12) = 1.5071466996821221; m(10,13) = -1.4878275078414411; m(10,14) = -0.530065962833408; m(10,15) = -1.567296619956997; m(10,16) = 2.0954400238664057; m(10,17) = 0.5936659119768759; m(10,18) = -1.749844785138718; m(10,19) = -0.3662478793983658; 
		m(11,0) = 1.3644491988664085; m(11,1) = -1.2342530780518657; m(11,2) = -1.5578097714390555; m(11,3) = 0.2232009544308219; m(11,4) = 0.02818697383157301; m(11,5) = -0.7910784859543236; m(11,6) = -1.6954277505398494; m(11,7) = 1.1093672090468547; m(11,8) = -0.24573511829681077; m(11,9) = -0.550187212165625; m(11,10) = -1.2481594086620302; m(11,11) = 9.48436826751276; m(11,12) = -0.46324928580670277; m(11,13) = -1.6627614758451332; m(11,14) = 1.0065149992560638; m(11,15) = -1.8385708282846784; m(11,16) = 0.37662525972164174; m(11,17) = -0.3835566088736359; m(11,18) = -0.7717605939193444; m(11,19) = -0.1501632448270697; 
		m(12,0) = -1.1655819810620596; m(12,1) = -0.2166829869417958; m(12,2) = -1.4508136306428177; m(12,3) = 0.26577320569953433; m(12,4) = 0.25670781668264986; m(12,5) = -0.4084637721729303; m(12,6) = 0.13616344280998272; m(12,7) = -0.1637605700083815; m(12,8) = -0.050618202875799996; m(12,9) = 0.16635671326089554; m(12,10) = 1.5071466996821221; m(12,11) = -0.46324928580670277; m(12,12) = 4.365734448382918; m(12,13) = -2.05647204396691; m(12,14) = -0.17104630982033608; m(12,15) = 0.8290068704049125; m(12,16) = 0.3382047105712041; m(12,17) = -0.9162750432692977; m(12,18) = -0.23084754509390018; m(12,19) = 0.42871746416671347; 
		m(13,0) = 1.3950776002855854; m(13,1) = 0.724222283881546; m(13,2) = 1.756845257210287; m(13,3) = -3.849378381177347; m(13,4) = 2.5458420114891607; m(13,5) = -1.7918083624070256; m(13,6) = 0.5224593489232829; m(13,7) = 0.7730202493033265; m(13,8) = 1.5495212869358013; m(13,9) = -3.058211311077955; m(13,10) = -1.4878275078414411; m(13,11) = -1.6627614758451332; m(13,12) = -2.05647204396691; m(13,13) = 10.957807986755153; m(13,14) = -2.1424454312931873; m(13,15) = -1.4539197767500542; m(13,16) = -2.241109789423289; m(13,17) = 1.4101388726855548; m(13,18) = -1.0786086460705757; m(13,19) = 0.1876078283832182; 
		m(14,0) = -0.8730336229158846; m(14,1) = 0.225912610815319; m(14,2) = -0.014460697272117372; m(14,3) = 0.5517126415557532; m(14,4) = -0.5486053649680269; m(14,5) = 0.8238072669516932; m(14,6) = -1.6482910320851194; m(14,7) = 0.4755144452040677; m(14,8) = -4.656229128444837; m(14,9) = 1.5817727477406398; m(14,10) = -0.530065962833408; m(14,11) = 1.0065149992560638; m(14,12) = -0.17104630982033608; m(14,13) = -2.1424454312931873; m(14,14) = 6.7140649790814075; m(14,15) = -0.8388973857480531; m(14,16) = 1.151141453032716; m(14,17) = 0.37251839186936053; m(14,18) = 0.07710023718774611; m(14,19) = -0.5569848373137956; 
		m(15,0) = -1.133042907802999; m(15,1) = 0.15601500304851568; m(15,2) = 0.36626896693032396; m(15,3) = 0.00650683192043492; m(15,4) = 0.4917817293663597; m(15,5) = -2.5766847148194616; m(15,6) = -0.7935789576914996; m(15,7) = -0.2794715244282062; m(15,8) = -0.33337186178847716; m(15,9) = 2.218594753049418; m(15,10) = -1.567296619956997; m(15,11) = -1.8385708282846784; m(15,12) = 0.8290068704049125; m(15,13) = -1.4539197767500542; m(15,14) = -0.8388973857480531; m(15,15) = 12.959028342805984; m(15,16) = -7.236065358607275; m(15,17) = 0.7173853446548597; m(15,18) = 0.35320104619938203; m(15,19) = 0.9531110474975115; 
		m(16,0) = -1.2982500738664329; m(16,1) = 0.7762269203999075; m(16,2) = -1.9742749695115842; m(16,3) = 0.6521703895101867; m(16,4) = 0.8189317184179818; m(16,5) = 0.14082153503785938; m(16,6) = -1.3267173787123192; m(16,7) = 0.8044036043399664; m(16,8) = 0.04019787851854289; m(16,9) = -0.2775230283900285; m(16,10) = 2.0954400238664057; m(16,11) = 0.37662525972164174; m(16,12) = 0.3382047105712041; m(16,13) = -2.241109789423289; m(16,14) = 1.151141453032716; m(16,15) = -7.236065358607275; m(16,16) = 15.427882596939474; m(16,17) = -5.406044481557453; m(16,18) = -1.3305075920137917; m(16,19) = -0.5315534182737113; 
		m(17,0) = -3.0012170674801575; m(17,1) = 1.1238489162860679; m(17,2) = 0.9329900095630002; m(17,3) = -0.2814422133508827; m(17,4) = 0.4617931031901016; m(17,5) = 0.538159075122896; m(17,6) = 0.987828419194378; m(17,7) = -3.4692907160962365; m(17,8) = -0.2174957912971931; m(17,9) = -3.7157530121819082; m(17,10) = 0.5936659119768759; m(17,11) = -0.3835566088736359; m(17,12) = -0.9162750432692977; m(17,13) = 1.4101388726855548; m(17,14) = 0.37251839186936053; m(17,15) = 0.7173853446548597; m(17,16) = -5.406044481557453; m(17,17) = 12.843004007527739; m(17,18) = -1.5324921185400842; m(17,19) = -0.05776499942398498; 
		m(18,0) = 3.171270388142828; m(18,1) = -4.491300862131707; m(18,2) = -0.9794964566164313; m(18,3) = 1.0755483805816946; m(18,4) = -1.4775196206150571; m(18,5) = 0.5017223428129025; m(18,6) = 0.23611172686753357; m(18,7) = -0.2246396468256504; m(18,8) = 0.26108739797930125; m(18,9) = 1.7939562592872373; m(18,10) = -1.749844785138718; m(18,11) = -0.7717605939193444; m(18,12) = -0.23084754509390018; m(18,13) = -1.0786086460705757; m(18,14) = 0.07710023718774611; m(18,15) = 0.35320104619938203; m(18,16) = -1.3305075920137917; m(18,17) = -1.5324921185400842; m(18,18) = 9.893268265106242; m(18,19) = -2.496248177199605; 
		m(19,0) = -0.32702618183130516; m(19,1) = 0.5223083545691525; m(19,2) = 0.1281426769119465; m(19,3) = -0.4257460464524473; m(19,4) = -1.77747987052491; m(19,5) = -0.44126873105214004; m(19,6) = -0.9069857784540717; m(19,7) = 0.3972743705320977; m(19,8) = -0.22130401566702068; m(19,9) = 0.2287503719332163; m(19,10) = -0.3662478793983658; m(19,11) = -0.1501632448270697; m(19,12) = 0.42871746416671347; m(19,13) = 0.1876078283832182; m(19,14) = -0.5569848373137956; m(19,15) = 0.9531110474975115; m(19,16) = -0.5315534182737113; m(19,17) = -0.05776499942398498; m(19,18) = -2.496248177199605; m(19,19) = 6.412861066424568; 
		inverse_covar = m;
	};
	void log(ostream &out) const
	{
		out << endl << "Solve Param:";
		out << endl << "lambda_min\t"	<< lambda_min;
		out << endl << "lambda_max\t"	<< lambda_max;
		out << endl << "precision\t"	<< precision;
		out << endl << "max_iterations\t" << max_iterations;
		out << endl << "m_lambda_grouping\t";
		switch(lambda_grouping)
		{
		case ONE_COVAR :	out << "ONE_COVAR"; break;
		case GROUP_COVAR :	out << "GROUP_COVAR"; break;
		case ONE_LAMBDA :	out << "ONE_LAMBDA"; break;
		case GROUP_LAMBDA : out << "GROUP_LAMBDA"; break;
		default: throw BPException("Invalid Lambda Grouping");
		}
		out << endl << "group_size\t"  << group_size;
		out << endl << "Covar" << endl <<inverse_covar;
	}

} ;


class CSMMSolve
{
public:
	CSMMSolve(void);
	~CSMMSolve(void);
public:
	void InitSolver(const CSMMSet &set, const InitParamSolve & sp);
	void SolveX(const CSMMSet &set, const CNumVec & param);
public:
	const CNumVec &GetX()			const {return(m_x);};
	const CNumVec &GetLambda()		const {return(m_lambda);}; // last lambda calculated from m_param

private: // Solver parameters
	LAMBDA_GROUPING m_lambda_grouping;
	double		m_lambda_min;
	double		m_lambda_max;
	double		m_precision;
	double		m_max_iterations;
	CNumMat m_inv_covar;
private: // to store solutions
	CNumVec m_x;
	CNumVec m_lambda;
private:  // Parameters for lambda group, mappings and covariance
	unsigned	m_group_size;
	unsigned	m_group_num;
	unsigned	m_vec_length;
private: // precalculated + intermediate values
	CNumMat m_tAA;
	CNumVec	m_y_inequal;
	CNumMat tAA_lam;
	CNumMat tAA_lam_inv;
private: // Help Functions
	void CalcX_inequal(const CSMMSet &set, const CNumMat & inverse);
};

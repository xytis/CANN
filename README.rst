*************
How to start?

Project is based on CMake system. If You wish to use any IDE, please check CMake man pages if it is supported. Currently these commands work:
-  cmake -G "CodeBlocks - Unix Makefiles" .
-  cmake -G "Eclipse CDT4 - Unix Makefiles" .
-  cmake -G "Kdevelop3" .

****
CANN
****
Cikliniai tinklai pagrįsti nenutrūkstamu signalų interpretavimu. Priešingai nei 
paprasti ANN čia vienam signalui pereiti per tinklą gali prireikti daugiau nei 
vieno perrinkimo. Tai yra lėtesnis būdas, tačiau atmintis šiuose tinkluose eg-
zistuoja dėl jų sandaros. Ir uždelsto veikimo.

Tikslai: Per vasarą parašyti pirmą veikiantį tinklą ir jį išbandyti su paprasta 
simuliacija.

Simuliacijos aprašas:
	CANN tinklo valdomas kvadratėlis egzistuoja gradientiškai palankioje
	aplinkoje. Aplinkos palankumo koeficientas duodama kaip vienintelė įves-
	tis. Išvestis -- vienas skaičius, teigiamas arba neigiamas, greitis
	kuriuo kvadratėlis juda pasaulyje. (pasaulis 1 dimensijos.) Pritaikius 
	genetinį algoritmą išvesti veislę, kuri laikytųsi palankiuose taškuose.
	(Čia pagal vienaląsčių elgesį jiem nepalankioje terpėje.)
	Išsivystymo taškai skaičiuojami pagal laiką praleistą palankioj vietoj, 
	laiką praleistą blogoje erdvėje, judrumą blogoje erdvėje.
Paturbintas aprašas:
  Vieną vakarą, sėdėdamas sugalvojau kad viskas gali vyktį šešiakampių plokštelių
  pasaulyje. Tai atneštų privalumų "gyvybės" organizavimui, bei jos gebėjimams.
  Taigi dabartinis tikslas sukurti CANN tinklą, prie kurio prisijungtų klasikiniai
  ANN tinklai (septyni input ir vienas output) ir kuris gebėtų sulipti su kitu(ais)
  CANN tinkliukais. T.y. gyvūnėlis (pavadinkime jį hex'u) būdamas ant laukelio su 6
  kraštinėm (daa, šešiakampis =]) "jaučia" (gauna įvestį) apie 6 kaimyninių laukelių
  ir apie laukelio ant kurio stovi būkles (papraščiausiu atveju 1 double maisto kiekį).
  Iš čia 7 input'ai, kurie apdoroja raw įvestį ir pritaiko ją CANN tinklui. Tada CANN
  tinkle turi imti cirkuliuoti nykstama (arba ne... čia dar mistika) mintis. Tos minties
  atgarsius output'o tinkliukas turi paversti 2d vektoriaus koordinatėmis, kurias
  naudotume gyvūno pajudėjimui įforminti. Esant dviems hex'ams šalia, jų sensoriai
  (ANN tinklai) konvertuojasi į tiltą tarp dviejų CANN. Mintys iš vieno tinklo turi
  persiduoti į kitą. (Net neįsivaizduoju ką tai atneš, bet turėtų būti įdomu.
      Na, pradžiai tai turbūt gyvūnėliai atšoks vienas nuo kito lyg nudeginti...)
  Kaip skaičiuojamas gyvūnėlių lifespan:
    hex'as turi pradinį food rezervą.
    su laiku food mažėja.
    NEJUDANT food galima gauti iš laukelio ant kurio stovi.
    susijungus su kitu gyvūnėliu food mažėja lėčiau (čia kad susijungimas būtų gerai)
    
  Ilgiausiai išgyvenęs gyvūnėlis tampa bandos alpha =] ir pasidaugina. Su nedideliu random'u.
  Tai vat. Bandom. Rašom. Gal išeis. =]

********************************************************************************
**                                 cNeuron                                    **
********************************************************************************
  Trumpai apie cNeuron:
  Tai yra neuronas.
  Vat. Viskas aišku?? Ne?
  Na tada: cNeuron gali būti sužadintas arba ne. Kai jis yra sužadintas, jis
  emituoja signalus į prie jo prijungtus neuronus ir juos žadina.
  Sužadinimas gali būti stačiakampio tipo (ala if sakinys) arba ne.
  Šiuo atveju naudojama sigmoid funkcija, kuri leidžia švelnesnius perėjimus ir
  tarpines būsenas.
  Kai neuronas gauna signalą iš kito neurono, jis jį sumuoja. Suma ir bus tas 
  skaičius, kuris apspręs ar neuronas kitą ciklą bus sužadintas ar ne.
  Vertės: signalai būna tarp 0 ir 1. Jei suma viršija 1, tai kai perkošiama su 
  sigmoid vertė vėl tampa tarp 0 ir 1.

  sigmoid(x) = 1/(1+exp(-x)) =]

  cNeuron veikia dviem etapais:
    send/get  --  siunčia visiem signalus
    flip      --  perverčia gautą sumą per sigmoid ir išsisaugo kaip aktyvacijos vertę.

  Šios simuliacijos tikslu pritaikyti std::map, sąryšiams tarp ID, fizinio adreso ir 
  efektinių jungties konstantų (čia tipo sinapsės pralaidumas) laikyti.

  Jei dar kas neaišku, o domina nerealiai -- skaitykit parašytą sourc'ą ir rašykit man.

  Vytis <xytis2000@gmail.com>


********************************************************************************
**                           SDL Interface                                    **
********************************************************************************

  Akivaizdu kad programa su grafiniu atvaizdavimu turi remtis kažkokia grafine biblioteka.
  Aš pasirinkau libSDL.

  Kaip bus suklijuotas programos veikimas:
    (SI - single instance (singleton) klasės
     VI - virtual interface klasės)

  SI cMainControler: užsiima SDL inicijavimu, laiko cProgramStates steką ir resursų
    controler'io adresą.
  SI cResourceControler: užsiima visų resursų inicijavimu\užkrovimu\išlaisvinimu.
    Išorinis pasaulis (ir kai kurie vidiniai resursai) turi būti prieinami būtent
    per šią klasę.
  VI cProgramState: virtualus programos būsenos interface'as. Palei jį kuriamos kitos būsenos
    Menu, Authors, Properties, Render...
  SI cRenderState: pagrindinė programos būsena, iš jos pagrindiniame lange atsiras gyvūnėliai,
    iš jos ir bus kviečiamas world_update ir gyvūnėlių mąstymas.
  VI cRenderObject: virtuali klasė visų atvaizduotinų objektų surišimui ir patogiam atvaizdavimui
    iš cRenderState. Mūsų pagrindinis veikėjas cCreature(a.k.a. Hex'as) irgi yra jos palikuonis.
    Tikiu kad ir kiti pasaulio objektai (jei jų bus) bus šios klasės palikuonys.

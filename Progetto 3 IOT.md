# Progetto 3 IOT



Obiettivo: creare un sistema di monitoraggio per il livello dell'acqua di un fiume e controllo di una diga.
in caso il livello dell'acqua sia troppo alto si controlla l'apertura della diga per far uscire l'acqua.

+ **l'esp** viene usato per monitorare il livello dell'acqua. comunica via http o mqtt con il back-end del pc. serve per raccogliere i dati ricevuti
+ **arduino** controlla la diga, comunica via seriale con il backend del pc e via bluetooth con **l'applicazione per smartphone**. il servo controlla l'apertura della diga.



STATI DEL SISTEMA:  

**normale** : non viene inviato nessun dato. 

**pre allarme** 

**allarme**



**memorizzare i dati**: al posto di db si può usare anche la memoria centrale.

**l'apertura della diga** non è o tutto o niente, ma è proporzionale al livello eccessivo di acqua (scegliamo noi).



**app mobile**: consente di

+ vedere lo stato del sistema
+ ultima rilevazione del livello e apertura diga
+ posso entrare in modalità di controllo della diga manuale (solo quando è allarme). Serve per selezionare l'apertura della diga.



se la frequenza è bassa è possibile passare da normale a allarme.



il front end è solo di visualizzazione. deve anche visualizzare se il controllo è automatico o manuale

la macchina a stati finiti può essere sincrona o asincrona

dam service ad esempio con vertex con java.

password e ssid li mettiamo a mano.







idee: 

incominciare dal sensore esp e farlo comunicare con il backend. 
successivamente implementare la gestione della diga in modalità automatica con arduino. 
creare poi l'app per smartphone e metterla in comunicazione con backend e arduino e infine creare interfaccia per la visualizzazione dati (per necessità di testing si può creare una versione minimale anche prima).



il sonar ha il compito di controllare il led e il sonar e inviare eventuali dati al backend.



è il backend che dopo aver ricevuto i dati comunica ad arduino di quando aprire la diga.



----


TASK : blinking, tracking, sending, controller.

WaterLevel: un oggetto che contiene il livello dell'acqua misurato. Tracking setta il livello. Sending lo legge e invia. 

Controller: legge il livello dell'acqua e decide lo stato del sistema e di conseguenza attiva e disattiva gli altri task. 

il backend viene a sapere dello stato del sistema dall'esp, non lo ricalcola.

---





































 
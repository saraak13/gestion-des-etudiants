#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

struct Date {
    int day;
    int month;
    int year;

    bool operator==(const Date& other) const {
        return (day == other.day) && (month == other.month) && (year == other.year);
    }
};

class Personne {
protected:
    string nom;
    string prenom;
    int age;
    int numeroTele;

public:
    // Constructor
    Personne(){}
    Personne(const string& nom, const string& prenom, int age, const int& numeroTele)
        : nom(nom), prenom(prenom), age(age), numeroTele(numeroTele) {
        }

    // Destructor
    virtual ~Personne() {}

    // Getters
    string getNom() const { return nom; }
    string getPrenom() const { return prenom; }
    int getAge() const { return age; }
    int getNumeroTele() const { return numeroTele; }

    // Setters
    void setNom(const string& nom) { this->nom = nom; }
    void setPrenom(const string& prenom) { this->prenom = prenom; }
    void setAge(int age){this->age = age; }
    void setNumeroTele(const int& numeroTele)
    { this->numeroTele = numeroTele;}

    // Methods
    virtual void afficher() const {
        cout << "Nom: " << nom << ", Prenom: " << prenom << ", Age: " << age
             << ", Numero de telephone: " << numeroTele << endl;
    }
    virtual void actualiserDetails(const string& nom, const string& prenom, int age, const int& numeroTele)
    {   string numeroStr = to_string(numeroTele);
        if (age >= 15 && numeroStr.length() == 8)
        {
        this->nom = nom;
        this->prenom = prenom;
        this->age = age;
        this->numeroTele = numeroTele;}
        else
        {cout <<"L'age doit etre superier a 15 ans et le numero de telephone doit avoir 8 chiffres" << endl;}
    }
  virtual void saveToFile(const string& filename) const = 0;
  virtual void loadFromFile(const string& filename) = 0;
};

// Class: Enseignant
class Enseignant : public Personne {
private:
    vector<string> matieres;
    vector<string> niveaux;
    Date dateRecrutement;
    float salaire;
    string idEnseignant;
    int vacances;
public:
    // Constructor
    Enseignant(){}
    Enseignant(const string& nom, const string& prenom, int age, const int& numeroTele,
     Date date_recrutement, float salaire, const string& id_enseignant)
        : Personne(nom, prenom, age, numeroTele) {
    this->dateRecrutement.day = date_recrutement.day;
    this->dateRecrutement.month = date_recrutement.month;
    this->dateRecrutement.year = date_recrutement.year;
    this->salaire = salaire;
    this->idEnseignant = id_enseignant;
    this->vacances = 60;
}

    // Destructor
    ~Enseignant() {}

    // Getters and Setters
    vector<string> getMatieres() const { return matieres; }
    void setMatieres(const vector<string>& matieres) { this->matieres = matieres; }
    vector<string> getNiveaux() const { return niveaux; }
    void setNiveaux(const vector<string>& niveaux) { this->niveaux = niveaux; }
    Date getDateRecrutement() const { return dateRecrutement; }
    void setDateRecrutement(Date date_recrutement) {
    this->dateRecrutement.day = date_recrutement.day;
    this->dateRecrutement.month = date_recrutement.month;
    this->dateRecrutement.year = date_recrutement.year; }
    float getSalaire() const { return salaire; }
    string getIdEnseignant() const { return idEnseignant; }
    void setIdEnseignant(const string& id_enseignant) { this->idEnseignant = id_enseignant; }
    int getVacances() const { return vacances; }
    void setVacances(int vacances) { this->vacances = vacances; }

    // Methods
    int calculerAnneesTravail() {
        time_t now = time(0); // Get current time
        tm *ltm = localtime(&now); // Convert to local time structure
        int currentYear = 1900 + ltm->tm_year; // Get current year
        return currentYear - dateRecrutement.year; // Assuming date_recrutement has a 'year' member
    }
     void AugmentationSalaireParAnnee() {
        int yearsWorked = calculerAnneesTravail();
        salaire += salaire * (1 + 0.02 * yearsWorked);
    }

    void updateSalary(float newSalary) {
    if (newSalary < 0) {
        cout << "Salary cannot be negative." << endl;
    } else {
        salaire = newSalary;
        cout << "Salary updated to: " << salaire << endl;
    }
}
    void afficher() {
        Personne::afficher();
        cout << "id enseignant: " << idEnseignant << ", salaire: " << salaire << ", Vacances: " << vacances
        << ", date recrutement:" << dateRecrutement.day << "/" << dateRecrutement.month << "/"
        << dateRecrutement.year << endl;
        cout << "matieres:" << endl;
        for (const auto& mat : matieres) {
            cout << mat << endl;
        }
         cout << "niveaux:" << endl;
        for (const auto& niv : niveaux) {
            cout << niv << endl;
        }
    }
    void ajouterMatiere(const string& matiere){
      auto it = find(matieres.begin(), matieres.end(), matiere);
      if (it == matieres.end())
      {matieres.push_back(matiere);}
    }
    void assignerNiveau(const string& niveau){
           auto it = find(niveaux.begin(), niveaux.end(), niveau);
      if (it == niveaux.end())
      {niveaux.push_back(niveau);}
    }
    void supprimerMatiere(string matiere) {
        auto it = find(matieres.begin(), matieres.end(), matiere);
        if (it != matieres.end()) {
            matieres.erase(it);
        }
    }
 void supprimerMatieres() {
        matieres.clear();
         }
    void supprimerNiveau(string niveau) {
        auto it = find(niveaux.begin(), niveaux.end(), niveau);
        if (it != niveaux.end()) {
            niveaux.erase(it);
        }
    }
 void supprimerNiveaux() {
        niveaux.clear();
         }
    void prendreVacances(int days) {
    if (days <= vacances) {
        vacances -= days;
        cout << "Vacation taken for " << days << " days. Remaining: " << vacances << " days." << endl;
    } else {
        cout << "Not enough vacation days available." << endl;
    }
}
 // Save to file
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << getNom() << "," << getPrenom() << "," << getAge() << "," << getNumeroTele()<< "," <<
            salaire << "," << idEnseignant << ","<< vacances << "," << dateRecrutement.day << "," << dateRecrutement.month << "," << dateRecrutement.year << endl;
            for (const auto& mat : matieres) {
                file << mat << ",";
            }
            file << endl; // New line after subjects
            file.close();
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    }
   void loadFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    if (getline(file, line)) {
        stringstream ss(line);
        getline(ss, nom, ',');
        getline(ss, prenom, ',');
        ss >> age;
        ss.ignore();
        ss >> numeroTele;
          ss.ignore();
        setNom(nom);
        setPrenom(prenom);
        setAge(age);
        setNumeroTele(numeroTele);
        ss >> salaire; // Ensure this is read correctly
        ss.ignore(); // Ignore the comma
        getline(ss, idEnseignant, ',');
        ss >> vacances;
          ss.ignore(); // Ignore the comma
          ss >> dateRecrutement.day;
          ss.ignore(); // Ignore the comma
          ss >> dateRecrutement.month;
          ss.ignore(); // Ignore the comma
          ss >> dateRecrutement.year;
    }
    if (getline(file, line)) {
        stringstream ss(line);
        string matiere;
        while (getline(ss, matiere, ',')) {
            if (!matiere.empty()) {
               // matieres.push_back(matiere);
            }
        }
    }
    file.close();
}
 friend istream& operator>>(istream& is, Enseignant& enseignant) {
    cout << "Enter Nom: ";
    is >> enseignant.nom;
    cout << "Enter Prenom: ";
    is >> enseignant.prenom;
    cout << "Enter Age: ";
    is >> enseignant.age;
    cout << "Enter Numero de telephone: ";
    is >> enseignant.numeroTele;
    cout << "Enter ID Enseignant: ";
    is >> enseignant.idEnseignant;
    cout << "Enter Salaire: ";
    is >> enseignant.salaire;
    cout << "Enter Date de recrutement (day, mounth, year): ";
    is >> enseignant.dateRecrutement.day >> enseignant.dateRecrutement.month >> enseignant.dateRecrutement.year ;
    enseignant.vacances = 60;

    return is;
}
};

// Class: matiere
class matiere {
private:
    string nom;
    Enseignant* enseignantResp;

public:
    // Constructors
    matiere(){}
    matiere(const string& nom, Enseignant* enseignantResp)
        : nom(nom), enseignantResp(enseignantResp) {}

    // Destructor
    ~matiere() {}

    // Getters
    string getNom() const { return nom; }
    Enseignant* getEnseignantResp() const { return enseignantResp; }
   string getEnseignantRespNom() const {
    return enseignantResp ? enseignantResp->getNom() : "No enseignant assigned";
}

    // Setters
    void setNom(const string& nom) { this->nom = nom; }
    void setEnseignantResp(Enseignant* enseignantResp) { this->enseignantResp = enseignantResp; }

    // Methods
    void afficher() const {
        cout << "Matiere: " << nom << endl;
        if (enseignantResp) {
            cout << "Enseignant responsable: " << enseignantResp->getNom() << endl;
        }
    }
    // Save to file
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << nom << "," << (enseignantResp ? enseignantResp->getNom() : "No enseignant assigned") << endl;
            file.close();
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    }

    // Load from file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string line;
        if (getline(file, line)) {
            stringstream ss(line);
            getline(ss, nom, ',');
            string enseignantNom;
            getline(ss, enseignantNom);
            // You might want to find the enseignant by name and assign it here
        }
        file.close();
    }
    friend istream& operator>>(istream& is, matiere& matiere) {
   string nom;
    cout << "Enter Nom: ";
    is >> matiere.nom;
    matiere.enseignantResp = nullptr;
    return is;
}
};

// Class: Etudiant
class Etudiant : public Personne {
private:
    vector<float> notes;
    vector<int> absence;
    vector<string> matieres;
    string idEtudiant;
    string niveau;
    Date anneeInscription;
public:
    // Constructor
    Etudiant(){}
   Etudiant(const string& nom, const string& prenom, int age, const int& numeroTele,
         const string& id_etudiant, const string& niveau,
         Date annee_inscription)
    : Personne(nom, prenom, age, numeroTele), idEtudiant(id_etudiant), niveau(niveau), anneeInscription(annee_inscription) {}

    // Destructor
    ~Etudiant() {}

    // Getters and Setters
    vector<float> getNotes() const { return notes; }
    void setNotes(const vector<float>& notes) { this->notes = notes; }
    vector<string> getMatieres() const { return matieres; }
    void setMatieres(const vector<string>& matieres) { this->matieres = matieres; }
    string getIdEtudiant() const { return idEtudiant; }
    void setIdEtudiant(const string& id_etudiant) { this->idEtudiant = id_etudiant; }
    string getNiveau() const { return niveau; }
    void setNiveau(const string& niveau) { this->niveau = niveau; }
    Date getAnneeInscription() const { return anneeInscription; }
    void setAnneeInscription(Date annee_inscription)
    {   this->anneeInscription.day = annee_inscription.day;
        this->anneeInscription.month = annee_inscription.month;
        this->anneeInscription.year = annee_inscription.year; }
    vector<int> getAbsence() const { return absence; }
    void setAbsence(const vector<int>& absence) { this->absence = absence; }

    // Methods
   void ajouterMatiere(const string& matiere, float note, int abs = 0) {
    auto it = find(matieres.begin(), matieres.end(), matiere);
    if (it == matieres.end()) {
        matieres.push_back(matiere);
        notes.push_back(note);
        absence.push_back(abs);
    } else {
        notes[it - matieres.begin()] = note; // Update existing note
        if (abs > absence[it - matieres.begin()]) {
            absence[it - matieres.begin()] = abs; // Update absence if greater
        }
    }
}
void supprimerMatiere(const string& matiere){
    auto it = find(matieres.begin(), matieres.end(), matiere);
    if(it != matieres.end())
    {
        matieres.erase(it);
        notes.erase(notes.begin() + (it - matieres.begin()));
        absence.erase(absence.begin() + (it - matieres.begin()));
    }
}
void supprimerMatieres(){
    matieres.clear();
    notes.clear();
    absence.clear();
}
void supprimerMatiere(const float seul){
   for(int i = 0; i < notes.size(); i++){
    if(notes[i] < seul){
        notes.erase(notes.begin() + i);
        matieres.erase(matieres.begin() + i);
        absence.erase(absence.begin() + i);
           }
   }
}
void incrementerAbsence(const string& matiere)
{ auto it = find(matieres.begin(), matieres.end(), matiere);
if(it != matieres.end())
{  absence[it - matieres.begin()]++;
}
else{
    cout <<"La matiere n'existe pas" << endl;
}
}
    void afficher() const override {
        Personne::afficher();
        cout << "ID Etudiant: " << idEtudiant << ", niveau: " << niveau
             << ", Année d'inscription: "<< anneeInscription.day << "/" << anneeInscription.month << "/"
             << anneeInscription.year<< endl;
        cout << "notes:" << endl;
        for (size_t i = 0; i < notes.size(); i++) {
            cout << "note de " << matieres[i] <<": "<< notes[i] << endl;
            cout << "absence: "<< absence[i] << endl;
        }
    }
    float moyenne() const {
        float sum = 0;
        for (size_t i = 0; i< notes.size(); i++)
        {
          sum += notes[i] - absence[i]*0.2;
        }
        return notes.empty() ? 0 : sum / notes.size();
    }
 int  absenceTotal() const {
        int s = 0;
        for (size_t i = 0; i< absence.size(); i++)
        {
          s += absence[i];
        }
    return s;
    }
    bool resultatFinale() {
        if(moyenne() < 10 || absenceTotal() > 30)
        {
            return false;
        }
        else
        {return true;}
    }
    // Save to file
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << getNom() << "," << getPrenom() << "," << getAge() << "," << getNumeroTele()
            << "," << idEtudiant << "," << niveau << "," << anneeInscription.day << "/"
                 << anneeInscription.month << "/" << anneeInscription.year << endl;
            for (size_t i = 0; i < matieres.size(); i++) {
                file << matieres[i] << "," << notes[i] << "," << absence[i] << endl;
            }
            file.close();
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    }
    void afficherNotes() const {
        for (size_t i = 0; i < notes.size(); i++) {
            cout << "note de " << matieres[i] <<": "<< notes[i] << endl;
            cout << "absence: "<< absence[i] << endl;
        }
    }
    // Load from file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string line;
        if (getline(file, line)) {
            stringstream ss(line);
        getline(ss, nom, ',');
        getline(ss, prenom, ',');
        ss >> age;
        ss.ignore();
        ss >> numeroTele;
          ss.ignore();
        setNom(nom);
        setPrenom(prenom);
        setAge(age);
        setNumeroTele(numeroTele);
         getline(ss, idEtudiant, ',');
         getline(ss, niveau, ',');
         int day, month, year;
            char delimiter; // For the '/' character
            ss >> day >> delimiter >> month >> delimiter >> year;
            anneeInscription = {day, month, year}; // Set the date
        }
        while (getline(file, line)) {
            stringstream ss(line);
            string matiere;
            float note;
            int abs;
            getline(ss, matiere, ',');
            ss >> note;
            ss.ignore(); // Ignore the comma
            ss >> abs;
            ajouterMatiere(matiere, note, abs);
        }
        file.close();
    }
// Overloading the >> operator
    friend istream& operator>>(istream& is, Etudiant& etudiant) {
        cout << "Enter Nom: ";
        is >> etudiant.nom;
        cout << "Enter Prenom: ";
        is >> etudiant.prenom;
        cout << "Enter Age: ";
        is >> etudiant.age;
        cout << "Enter Numero de telephone: ";
        is >> etudiant.numeroTele;
        cout << "Enter ID Etudiant: ";
        is >> etudiant.idEtudiant;
        cout << "Enter Niveau: ";
        is >> etudiant.niveau;
        cout << "Enter Date d'inscription (dd/mm/yyyy): ";
        is >> etudiant.anneeInscription.day >> etudiant.anneeInscription.month >> etudiant.anneeInscription.year;
        return is;
    }
};
// Class: Administration
class Administration : public Personne {
private:
    string role;
    Date dateRecrutement;
    float salaire;
    string id;
    int vacances;

public:
    // Constructor
    Administration(){}
Administration(const string& nom, const string& prenom, int age, const int& numeroTele,
               const string& role, const Date& date_recrutement, float salaire, const string& id)
    : Personne(nom, prenom, age, numeroTele) // Call base class constructor here
{
    this->role = role;
    this->dateRecrutement.day = date_recrutement.day;
    this->dateRecrutement.month = date_recrutement.month;
    this->dateRecrutement.year = date_recrutement.year;
    this->salaire = salaire;
    this->id = id;
    this->vacances = 60;
}
    // Destructor
    ~Administration() {}
    // Getters and Setters
    string getRole() const { return role; }
    void setRole(const string& role) { this->role = role; }
    Date getDateRecrutement() const { return dateRecrutement; }
    void setDateRecrutement(Date date_recrutement)
    {  this->dateRecrutement.day = date_recrutement.day;
    this->dateRecrutement.month = date_recrutement.month;
    this->dateRecrutement.year = date_recrutement.year; }
    float getSalaire() const { return salaire; }
    string getId() const { return id; }
    void setId(const string& id) { this->id = id; }
    friend class Etudiant;
   int getVacances() const { return vacances; }
   void setVacances(int vacances) { this->vacances = vacances; }

    // Methods
 int calculerAnneesTravail() {
        time_t now = time(0); // Get current time
        tm *ltm = localtime(&now); // Convert to local time structure
        int currentYear = 1900 + ltm->tm_year; // Get current year
        return currentYear - dateRecrutement.year; // Assuming date_recrutement has a 'year' member
    }
     void AugmentationSalaireParAnnee() {
        int yearsWorked = calculerAnneesTravail();
         int c;
        if (role == "responsable")
         {  c = 0,5;}
         else if(role == "chef")
         {  c = 0,4;}
         else if(role == "vice")
         {  c = 0,3;}
         else if(role == "technique")
         {  c = 0,2;}
         else if(role == "secretaire")
         {  c = 0,1;}
        salaire += salaire * (1 + c * yearsWorked);
    }
void updateSalary(float newSalary) {
    if (newSalary < 0) {
        cout << "Salary cannot be negative." << endl;
    } else {
        salaire = newSalary;
        cout << "Salary updated to: " << salaire << endl;
    }
}
void afficher() const {
    Personne::afficher(); // Call the base class afficher method
    cout << "Role: " << role
         << ", ID: " << id
         << ", Salaire: " << salaire
         << ", Vacances: " << vacances
         << ", Date Recrutement: "
         << dateRecrutement.day << "/"
         << dateRecrutement.month << "/"
         << dateRecrutement.year << endl;
}
    void avertissement(const Etudiant& etudiant) {
    if (etudiant.moyenne() < 10 || etudiant.absenceTotal() > 10) {
        cout << "Avertissement à " << etudiant.getNom() << endl;
    }else {
    cout << "Pas d'Avertissement à " << etudiant.getNom() << endl;}

}
void bonus(const Etudiant& etudiant) {
    if (etudiant.moyenne() > 18 && etudiant.absenceTotal() < 10) {
        cout << "Bonus à " << etudiant.getNom() << endl;
    }
    else {
    cout << "Pas de Bonus à " << etudiant.getNom() << endl;}
}
    void prendreVacances(int days) {
    if (days <= vacances) {
        vacances -= days;
        cout << "Vacation taken for " << days << " days. Remaining: " << vacances << " days." << endl;
    } else {
        cout << "Not enough vacation days available." << endl;
    }
}
   // Save to file
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            file << getNom() << "," << getPrenom() << "," << getAge() << "," << getNumeroTele()<< ","
            << role << "," << salaire << "," << id << "," << vacances << "," << dateRecrutement.day << "," << dateRecrutement.month << "," << dateRecrutement.year << endl;
            file.close();
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    }
    // Load from file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string line;
        if (getline(file, line)) {
            stringstream ss(line);
        getline(ss, nom, ',');
        getline(ss, prenom, ',');
        ss >> age;
        ss.ignore();
        ss >> numeroTele;
          ss.ignore();
        // Assuming you have a constructor or method to set these values
        setNom(nom);
        setPrenom(prenom);
        setAge(age);
        setNumeroTele(numeroTele);
            getline(ss, role, ',');
            ss >> salaire;
            ss.ignore(); // Ignore the comma
            getline(ss, id, ',');
            ss >> vacances;
            ss.ignore(); // Ignore the comma
             ss >> dateRecrutement.day;
             ss.ignore(); // Ignore the comma
             ss >> dateRecrutement.month;
             ss.ignore(); // Ignore the comma
             ss >> dateRecrutement.year;
        }
        file.close();
    }
friend istream& operator>>(istream& is, Administration& admin) {
    cout << "Enter Nom: ";
    is >> admin.nom;
    cout << "Enter Prenom: ";
    is >> admin.prenom;
    cout << "Enter Age: ";
    is >> admin.age;
    cout << "Enter Numero de telephone: ";
    is >> admin.numeroTele;
    cout << "Enter Role: ";
    is >> admin.role;
    cout << "Enter Salaire: ";
    is >> admin.salaire;
    cout << "Enter ID: ";
    is >> admin.id;
    admin.vacances = 60;
    cout << "Enter Date Recrutement (day month year): ";
    is >> admin.dateRecrutement.day >> admin.dateRecrutement.month >> admin.dateRecrutement.year;
    return is;
}
};

// Class: delegue
class Delegue: public Etudiant {
private:
    string idDelegue;
    Date electedDate;
    vector<string> tasks;
    vector<bool> taskComplete;
    int performance;

public:
    // Constructors
    Delegue(){}
    Delegue(const string& nom, const string& prenom, int age, const int& numeroTele,
             const string& id_etudiant, const string& groupe,
             Date annee_inscription, const string& id, Date date)
        : Etudiant(nom, prenom, age, numeroTele, id_etudiant, groupe, annee_inscription)
           {
            this->idDelegue = id;
            this->electedDate.day = date.day;
            this->electedDate.month = date.month;
            this->electedDate.year = date.year;
            this->performance = 0;
          }

    Delegue(Etudiant* etud, const string& id, Date electedDate)
    : Etudiant(etud->getNom(), etud->getPrenom(), etud->getAge(), etud->getNumeroTele(), etud->getIdEtudiant(), etud->getNiveau(), etud->getAnneeInscription())
{
    this->idDelegue = id;
    this->electedDate.day = electedDate.day;
    this->electedDate.month = electedDate.month;
    this->electedDate.year = electedDate.year;
    this->performance = 0;
}
    // Destructor
    ~Delegue() {}

    // Getters
    string getIdDelegue() const { return idDelegue; }
    Date getElectedDate() const { return electedDate; }
    int getPerformance() const { return performance; }
    const vector<string>& getTasks() const { return tasks; }
    const vector<bool>& getTaskComplete() const { return taskComplete; }

    // Setters
    void setIdDelegue(const string& id) { idDelegue = id; }
    void setElectedDate(const Date& date)
    {       this->electedDate.day = date.day;
            this->electedDate.month = date.month;
            this->electedDate.year = date.year; }
    void setPerformance(int perf) { performance = perf; }

    // Methods
    void ajouterTache(const string& task) {
        auto it = find(tasks.begin(), tasks.end(), task);
        if (it == tasks.end()){
        tasks.push_back(task);
        taskComplete.push_back(false);
    }}
void completerTache(const string& task){
    auto it = find(tasks.begin(), tasks.end(), task);
    if(it != tasks.end())
    {
        taskComplete[it - tasks.begin()] = true;
    }
    else
    {
      tasks.push_back(task);
      taskComplete.push_back(true);
    }
}
void supprimerTache(const string& task){
    auto it = find(tasks.begin(), tasks.end(), task);
    if(it != tasks.end())
    {
        tasks.erase(it);
        taskComplete.erase(taskComplete.begin() + (it - tasks.begin()));
    }
}
void supprimerTaches(){
    tasks.clear();
    taskComplete.clear();
}
void supprimerTachesComplete(){
    for(size_t i = 0; i < taskComplete.size(); i++)
    {
        if(taskComplete[i] == true)
        {
            tasks.erase(tasks.begin() + i);
            taskComplete.erase(taskComplete.begin() + i);
        }  }
}

    void evaluation() {
        int c = 0;
        for(size_t i = 0; i < taskComplete.size(); i++){
            if(taskComplete[i] == true){
                c++;
            }
        }
        if(c == taskComplete.size()){
            performance = 10;
        }
        else if(c > taskComplete.size()/2){
            performance = 8;
        }
        else if (c > taskComplete.size()/4){
            performance = 6;
        }
        else if (c > 0){
            performance = 4;
        }
        else
        {
            performance = 0;
        }
        cout << "Delegue Performance: " << performance << endl;
    }
    void afficher(){
        Etudiant::afficher();
        cout << "ID Delegue: " << idDelegue << endl;
        cout << "Elected Date: " << electedDate.day << "/" << electedDate.month << "/" << electedDate.year << endl;
        cout << "Performance: " << performance << endl;
        cout << "Tasks: " << endl;
        for(size_t i = 0; i < tasks.size(); i++){
            cout << tasks[i] << ":";
            if(taskComplete[i] == true){
                cout << "Completed" << endl;
            }
            else{
                cout << "Not Completed" << endl;
            }
        }
    }
     // Save to file
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
file << getNom() << "," << getPrenom() << "," << getAge() << "," << getNumeroTele()
            << "," << getIdEtudiant() << "," << getNiveau() << "," << getAnneeInscription().day << "/"
                 << getAnneeInscription().month << "/" << getAnneeInscription().year << ","
                 << idDelegue << "," << electedDate.day << "/"
                 << electedDate.month << "/" << electedDate.year << ","
                 << performance << endl;
            for (size_t i = 0; i < tasks.size(); i++) {
                file << tasks[i] << "," << taskComplete[i] << endl;
            }
            file.close();
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    }
    // Load from file
   void loadFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    string idEtudiantTemp;
    string niveauTemp;
    if (file.is_open()) {
        // Read the first line
        if (getline(file, line)) {
            stringstream ss(line);
            getline(ss, nom, ',');
            getline(ss, prenom, ',');
            ss >> age;
            ss.ignore();
            ss >> numeroTele;
            ss.ignore();
            // Set the values using the setter functions
            setNom(nom);
            setPrenom(prenom);
            setAge(age);
            setNumeroTele(numeroTele);
            // Read ID and Niveau
            getline(ss, idEtudiantTemp, ',');
            getline(ss, niveauTemp, ',');
            setIdEtudiant(idEtudiantTemp);
            setNiveau(niveauTemp);
            // Read the date of inscription
            int day, month, year;
            char delimiter; // For the '/' character
            ss >> day >> delimiter >> month >> delimiter >> year;
            setAnneeInscription({day, month, year}); // Set the date
                 getline(ss, idDelegue, ',');
            ss >> day >> delimiter >> month >> delimiter >> year;
            electedDate = {day, month, year}; // Set the date
            ss >> performance;}
        // Read the remaining lines for tasks
        while (getline(file, line)) {
            stringstream ss(line);
            string task;
            bool complete;
            getline(ss, task, ',');
            ss >> complete;
          //  tasks.push_back(task);
          //  taskComplete.push_back(complete);
        }
        file.close();
    } else {
        cout << "Unable to open file for reading." << endl;
    }
}
friend istream& operator>>(istream& is, Delegue& delegue) {
    cout << "Enter ID Delegue: ";
    is >> delegue.idDelegue;
    cout << "Enter Elected Date (day month year): ";
    is >> delegue.electedDate.day >> delegue.electedDate.month >> delegue.electedDate.year;
    cout << "Enter Performance: ";
    is >> delegue.performance;
    return is;
}
};
// Class: groupe
class Groupe {
private:
    vector<Etudiant*> etudiants;
    vector<Date> dateExamen;
    vector<matiere*> matieres;
    string niveau;
    Delegue* groupeDelegue;
    float moyenneGroupe;
    int numero;
public:
    // Constructors
    Groupe(){}
    Groupe(const string& niveau,const int& numero)
        : niveau(niveau), numero(numero) {}
    // Destructor
    ~Groupe() {
    for (auto& mat : matieres) {
        delete mat; // Clean up dynamically allocated matieres
    }
    for (auto& etud : etudiants) {
        delete etud; // Clean up dynamically allocated students
    }
    delete groupeDelegue; // Clean up dynamically allocated delegue
}
    // Getters
    vector<Date> getDateExamen() const { return dateExamen; }
    string getNiveau() const { return niveau; }
    Delegue* getDelegue() const { return groupeDelegue; }
    const vector<Etudiant*> getEtudiants() const { return etudiants; }
    const vector<matiere*> getMatieres() const { return matieres; }
    float getMoyenneGroupe() const { return moyenneGroupe;}
    int getNumero() const { return numero;}
    // Setters
    void setNiveau(const string& niveau) { this->niveau = niveau; }
    void setDelegue(Delegue* deleguePtr) { groupeDelegue = deleguePtr; }
    void setNumero(int num){ this->numero = num;}
    // Methods
    void ajouterEtudiant( Etudiant* etudiant) {
        this->etudiants.push_back(etudiant);
    }
  void supprimerEtudiant( Etudiant* etudiant) {
       auto it = find(etudiants.begin(), etudiants.end(), etudiant);
       if(it != etudiants.end()){
        etudiants.erase(it);
       }
    }
  void supprimerEtudiants() {
        etudiants.clear();
    }
void supprimerEtudiantParNiveau() {
        for(size_t i = 0; i < etudiants.size(); i++)
        {
            if(etudiants[i]->getNiveau() != niveau){
                etudiants.erase(etudiants.begin() + i);
                i--;
            }
        }   }
    void supprimerEtudiantParId( string id) {
       for(size_t i = 0; i < etudiants.size(); i++){
        if(etudiants[i]->getIdEtudiant() == id){
            etudiants.erase(etudiants.begin() + i);
            break;
        }
       }  }
 void supprimerEtudiantParMoyenne(float seul){
    for(size_t i = 0; i < etudiants.size(); i++)
       {
           if(etudiants[i]->moyenne() < seul){
               etudiants.erase(etudiants.begin() + i);
               i--;
           }
       }
   }
    void ajouterDateExamen(const Date& date, matiere* mat) {
        auto it = find(dateExamen.begin(), dateExamen.end(), date);
        if(it != dateExamen.end()){
            cout <<"date deja reserver" << endl;
        }
        else{
        auto itt = find(matieres.begin(), matieres.end(), mat);
            if(itt == matieres.end()){
                matieres.push_back(mat);
                dateExamen.push_back(date);
            }
            else
            {
            dateExamen[itt - matieres.begin()] = date;
            }
        }
        }
    void supprimerDateExamen(const Date& date){
     auto it = find( dateExamen.begin(), dateExamen.end(), date);
     if(it != dateExamen.end()){
        dateExamen[it - dateExamen.begin()].day  = 0;
        dateExamen[it - dateExamen.begin()].month  = 0;
        dateExamen[it - dateExamen.begin()].year  = 0;
     }
    }
    void supprimerDateExamen(const matiere* mat){
     auto it = find( matieres.begin(), matieres.end(), mat);
     if(it != matieres.end()){
        dateExamen[it - matieres.begin()].day  = 0;
        dateExamen[it - matieres.begin()].month  = 0;
        dateExamen[it - matieres.begin()].year  = 0;
     }
     else
    {cout << "matiere n'existe pas" << endl;}
    }
    void ajouterMatiere(matiere* mat) {
        Date date;
        date.day = 0;
        date.month = 0;
        date.year = 0;
        matieres.push_back(mat);
        dateExamen.push_back(date);
    }
     void supprimerMatiere(matiere* mat) {
      auto it = find( matieres.begin(), matieres.end(), mat);
     if(it != matieres.end()){
        matieres.erase(it);
        dateExamen.erase(dateExamen.begin() + (it - matieres.begin()));
     }
    }
 void supprimerMatieres() {
      matieres.clear();
      dateExamen.clear();
     }
    void afficher() const {
        cout << "Groupe - Niveau: " << niveau << ", Numero:" << numero <<endl;
            cout << "Delegue: " << groupeDelegue->getNom() << " "<< groupeDelegue->getPrenom()<< endl;
        cout << "Etudiants: ";
        for (const auto& etu : etudiants) {
            cout << etu->getNom() << " "<< etu->getPrenom()<< endl;
        }
        cout << endl;
for(size_t i = 0; i < matieres.size(); i ++){
    cout << "Matiere:" << matieres[i]->getNom() << endl;
    cout << "Date Examen:" << dateExamen[i].day << "/" <<
    dateExamen[i].month << "/" << dateExamen[i].year <<  endl;
}
    }
    void planifierEvenement(Date date) const {
        auto it = find(dateExamen.begin(), dateExamen.end(), date);
        if (it == dateExamen.end())
        { cout << "Evenement planifié." << endl;}
        else
        {cout << "il ya un examen ce jour" << endl;}
    }
    void changerDelegue(){
        if (groupeDelegue->getPerformance()< 5)
        {cout << "il faux changer le delegue" << endl;}
        else
        {cout << "il ya un bon delegue" << endl;}
    }
    float moyenne() {
    float sum = 0;
    for (size_t i = 0; i< etudiants.size(); i++)
    {
        sum += etudiants[i]->moyenne();
    }
    moyenneGroupe =  sum / etudiants.size();
     return etudiants.empty() ? 0 : sum / etudiants.size();
}
 int nbValidation() {
    int c = 0;
    for (size_t i = 0; i < etudiants.size(); i++) {
        if (etudiants[i]->resultatFinale()) {
            c++;
        }
    }
    return c; // Return the count of validated students
}
    // Save to file
void saveToFile(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << niveau << "," << numero << endl;
        for (const auto& etud : etudiants) {
            etud->saveToFile(filename); // Call save method for each student
        }
        for (const auto& mat : matieres) {
            mat->saveToFile(filename); // Call save method for each subject
        }
        file.close();
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}
    // Load from file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string line;
        if (getline(file, line)) {
            stringstream ss(line);
            getline(ss, niveau, ',');
            ss >> numero;
        }
        while (getline(file, line)) {
            // Assuming a method to create a new student based on the line
            Etudiant* etudiant = new Etudiant();
            etudiant->loadFromFile(filename); // Load student data
            etudiants.push_back(etudiant);
        }
        file.close();
    }
friend istream& operator>>(istream& is, Groupe& groupe) {
    cout << "Enter numero: ";
    is >> groupe.numero;
    cout << "Enter Niveau: ";
    is >> groupe.niveau;


// Allocate memory for groupe.groupeDelegue
groupe.groupeDelegue = new Delegue(); 

// Optionally, you can also read values into groupe.groupeDelegue here
// e.g., is >> *groupe.groupeDelegue; // Assuming Delegue has an overloaded operator>>
    
    return is;
}
};
int chercher(string n1, string n2, vector<Administration*> admin)
{
    for(size_t i = 0; i < admin.size(); i++){
        if(admin[i]->getNom() == n1 && admin[i]->getPrenom() == n2){
            return i;
        }
    }
    return -1;
}
int chercher(string n1, string n2, vector<Enseignant*> admin)
{
    for(size_t i = 0; i < admin.size(); i++){
        if(admin[i]->getNom() == n1 && admin[i]->getPrenom() == n2){
            return i;
        }
    }
    return -1;
}

int chercher(string n1, string n2, vector<Etudiant*> admin)
{
    for(size_t i = 0; i < admin.size(); i++){
        if(admin[i]->getNom() == n1 && admin[i]->getPrenom() == n2){
            return i;
        }
    }
    return -1;
}

int chercher(string n1, string n2, vector<Delegue*> admin)
{
    for(size_t i = 0; i < admin.size(); i++){
        if(admin[i]->getNom() == n1 && admin[i]->getPrenom() == n2){
            return i;
        }
    }
    return -1;
}

int chercher(string n1, int n2, vector<Groupe*> admin)
{
    for(size_t i = 0; i < admin.size(); i++){
        if(admin[i]->getNiveau() == n1 && admin[i]->getNumero() == n2){
            return i;
        }
    }
    return -1;
}
int chercher(string n1,vector<matiere*> admin)
{
    for(size_t i = 0; i < admin.size(); i++){
        if(admin[i]->getNom() == n1){
            return i;
        }
    }
    return -1;
}

int chercherGroupeParEtudiant(string n1,string n2,vector<Groupe*> admin)
{
    for(size_t i = 0; i < admin.size(); i++){
        for(size_t z = 0; z < admin[i]->getEtudiants().size(); z++){
            if(admin[i]->getEtudiants()[z]->getNom() == n1 && admin[i]->getEtudiants()[z]->getPrenom() == n2){
                return i;
            }
        }
    }
    return -1;
}

void afficher(vector<Administration*> admin)
{
    for(size_t i = 0; i < admin.size(); i++){
        admin[i]->afficher();
        cout<<"*****************" <<endl;
    }
}
void afficher(vector<Enseignant*> admin)
{
    for(size_t i = 0; i < admin.size(); i++){
        admin[i]->afficher();
        cout<<"*****************" <<endl;
    }
}

void afficher(vector<Etudiant*> admin)
{
    for(size_t i = 0; i < admin.size(); i++){
        admin[i]->afficher();
        cout<<"*****************" <<endl;
    }
}
void afficher(vector<Groupe*> admin)
{
    for(size_t i = 0; i < admin.size(); i++){
        admin[i]->afficher();
        cout<<"*****************" <<endl;
    }
}
void afficher(vector<matiere*> admin)
{
    for(size_t i = 0; i < admin.size(); i++){
        admin[i]->afficher();
        cout<<"*****************" <<endl;
    }
}
void supprimer(string n1, vector<matiere*> &admin) {
    // Find the index of the matiere to remove
    for (size_t i = 0; i < admin.size(); i++) {
        if (admin[i]->getNom() == n1) { // Assuming getNom() is a method of matiere
            admin.erase(admin.begin() + i); // Remove the matiere from the vector
            cout << "Matiere " << n1 << " supprimée." << endl;
            return; // Exit after removing
        }
    }
    cout << "Matiere " << n1 << " n'existe pas." << endl; // If not found
}


int main() {
     int choix = 0;
     int choix2 = 0;
     int j,i,x;
    string motdepasse = "0000";
    string mp, name, lastName;
    string name1;
    string name2;
    string name3;
    float salaire;
    int nombre;
    string matt;
      Date d1 ={1 ,1 , 2020};
      Date d2 ={14 ,12 , 2021};
    Administration admin;
    Enseignant ens;
    Etudiant etud;
    Groupe grp;
    matiere mat;
    Delegue del;

     Administration admin1("boughaba","rabia",41 , 6666,"responsable", d1, 20000,"A1");
     admin1.saveToFile("admin1.txt");
     Administration admin2("amrani","anas",31 , 6999,"technique", d2, 10000,"A2");
     admin2.saveToFile("admin2.txt");

      Enseignant ens1("abaru","nisrine",29 , 6666, d1, 30000,"T1");
      ens1.ajouterMatiere("P.O.O");
      ens1.ajouterMatiere("system d'exploitation");
      ens1.assignerNiveau("3IIR");
      ens1.assignerNiveau("2AP");
     ens1.saveToFile("enseignant1.txt");
      Enseignant ens2("alaoui","jamal",31 , 6999, d2, 30000,"T2");
     ens2.ajouterMatiere("PHP");
     ens2.assignerNiveau("3IIR");
     ens2.saveToFile("enseignant2.txt");

     matiere mat1("P.O.O",&ens1);
     mat1.saveToFile("matiere1.txt");
     matiere mat2("system d'exploitation",&ens1);
     mat2.saveToFile("matiere2.txt");
     matiere mat3("PHP",&ens2);
     mat3.saveToFile("matiere3.txt");

     Etudiant etud1("boughaba", "jihan", 21, 61111, "S1","3IIR",d1);
     etud1.ajouterMatiere("P.O.O", 12);
     etud1.ajouterMatiere("PHP", 14);
     etud1.saveToFile("etudiant1.txt");
     Etudiant etud2("akrouh", "sara", 20, 61112, "S2","3IIR",d1);
     etud2.ajouterMatiere("P.O.O", 19);
     etud2.ajouterMatiere("PHP", 19);
     etud2.saveToFile("etudiant2.txt");
     Etudiant etud3("morabit", "nahla", 21, 61113, "S3","3IIR",d1);
     etud3.ajouterMatiere("P.O.O", 17);
     etud3.ajouterMatiere("PHP", 16);
     etud3.saveToFile("etudiant3.txt");
     Etudiant etud4("berkani", "samir", 19, 61114, "S4","2AP",d2);
     etud4.ajouterMatiere("system d'exploitation", 14);
     etud4.saveToFile("etudiant4.txt");
     Etudiant etud5("dkiouak", "amal", 20, 61115, "S5","2AP",d2);
     etud5.ajouterMatiere("system d'exploitation", 10);
     etud5.saveToFile("etudiant5.txt");

     Delegue deleg1(&etud2,"D1", d1);
     deleg1.ajouterTache("creer group whatsapp");
     deleg1.ajouterTache("contacter les etudiants");
     deleg1.ajouterTache("organiser les taches");
     deleg1.completerTache("creer group whatsapp");
     deleg1.saveToFile("delegue1.txt");
     Delegue deleg2(&etud5,"D2", d2);
     deleg2.ajouterTache("contacter les etudiants");
     deleg2.ajouterTache("organiser les taches");
     deleg2.completerTache("creer group whatsapp");
     deleg2.completerTache("contacter les etudiants");
     deleg2.saveToFile("delegue2.txt");

Groupe grp1("3IIR",1);
grp1.ajouterEtudiant(&etud1);
grp1.ajouterEtudiant(&etud2);
grp1.ajouterEtudiant(&etud3);
grp1.ajouterMatiere(&mat1);
grp1.ajouterMatiere(&mat3);
grp1.ajouterDateExamen(d1,&mat1);
grp1.ajouterDateExamen(d2,&mat3);
grp1.setDelegue(&deleg1);
grp1.moyenne();
grp1.saveToFile("groupe1.txt");
Groupe grp2("2AP",1);
grp2.ajouterEtudiant(&etud4);
grp2.ajouterEtudiant(&etud5);
grp2.ajouterMatiere(&mat2);
grp2.ajouterDateExamen(d1,&mat2);
grp2.setDelegue(&deleg2);
grp2.moyenne();
grp2.saveToFile("groupe2.txt");

     vector<Administration*> admins;
     admins.push_back(&admin1);
     admins.push_back(&admin2);

     vector<Enseignant*> enseignants;
     enseignants.push_back(&ens1);
     enseignants.push_back(&ens2);

      vector<matiere*> matieres;
     matieres.push_back(&mat1);
     matieres.push_back(&mat2);
     matieres.push_back(&mat3);

     vector<Etudiant*> etudiants;
     etudiants.push_back(&etud1);
     etudiants.push_back(&etud2);
     etudiants.push_back(&etud3);
     etudiants.push_back(&etud4);
     etudiants.push_back(&etud5);

    vector<Delegue*> delegues;
     delegues.push_back(&deleg1);
     delegues.push_back(&deleg2);

    vector<Groupe*> groupes;
    groupes.push_back(&grp1);
    groupes.push_back(&grp2);

 while (choix != 5){

   cout << "*************************"<< endl;
   cout << "Menu:" << endl;
   cout << "1.Mode Admin" << endl;
   cout << "2.Mode Enseignant" << endl;
   cout << "3.Mode Delegue" << endl;
   cout << "4.Mode Etudiant" << endl;
   cout << "5.Quitter" << endl;
   cout << "Votre Choix:"<< endl;
   cout << "*************************"<< endl;

   cin >> choix;
   if(choix == 1){
cout << "Mode Admin" << endl;
cout << "Entrer Le Mot De Passe" << endl;
cin >> mp;
if(mp == motdepasse){
    while(choix2 != 34){
     cout << "*************************"<< endl;
   cout << "Menu:" << endl;
   cout << "1.Changer Mot De Passe" << endl;
   cout << "2.Augmenter Salaire Par Annees De Travail" << endl;
   cout << "3.Update Salaire" << endl;
   cout << "4.Avertir Un Etudiant" << endl;
   cout << "5.Donne Bonus A Un Etudiant" << endl;
   cout << "6.Prendre Vacances" << endl;
   cout << "7.Afficher Les Admins" << endl;
   cout << "8.Afficher Les Enseignants" << endl;
   cout << "9.Afficher Les Etudiants" << endl;
   cout << "10.Afficher Les Groupes" << endl;
   cout << "11.Afficher Les Matieres" << endl;
   cout << "12.Afficher Specifiquement" << endl;
   cout << "13.Afficher Le Nombre De Validation Dans Un Groupe" << endl;
   cout << "14.Ajouter Un Admin" << endl;
   cout << "15.Ajouter Un Enseignant" << endl;
   cout << "16.Ajouter Un Etudiant" << endl;
   cout << "17.Ajouter Un Groupe" << endl;
   cout << "18.Ajouter Une Matiere" << endl;
   cout << "19.Ajouter Un Delegue" << endl;
   cout << "20.Ajouter Une Matiere A Un Enseignant" << endl;
   cout << "21.Ajouter Une Matiere A Un Groupe" << endl;
   cout << "22.Assigner Un Niveau A Un Enseignant" << endl;
   cout << "23.Ajouter Un Etudiant A Un Groupe" << endl;
   cout << "24.Supprimer Une Matiere" << endl;
   cout << "25.Supprimer Une Matiere D'un Enseignant" << endl;
   cout << "26.Supprimer Une Matiere D'un Groupe" << endl;
   cout << "27.Supprimer Tous Les Matieres D'un Groupe" << endl;
   cout << "28.Supprimer Un Niveau D'un Enseignant" << endl;
   cout << "29.Supprimer Un Etudiant Dans Un Groupe" << endl;
   cout << "30.Supprimer Tous Les Etudiants Dans Un Groupe" << endl;
   cout << "31.Supprimer Un Etudiant Dans Un Groupe Par Son Id" << endl;
   cout << "32.Supprimer Un Etudiant Dans Un Groupe Par Son Niveau" << endl;
   cout << "33.Supprimer Un Etudiant Dans Un Groupe Par Son Moyenne" << endl;
   cout << "34.Quitter" << endl;
   cout << "Votre Choix:"<< endl;
   cout << "*************************"<< endl;
   cin >> choix2;

   switch (choix2)
   {
    case 1:
        cout << "Changement De Mot De Passe: "<< endl;
        cout << "Entrer Le Nouveau Mot De Passe" << endl;
        cin >> mp;
        motdepasse = mp;
        cout << "Mot De Passe Change Avec Succes" << endl;
        break;
    case 2:
        cout << "Augmentation De Salaire A:" << endl;
        cout << "Nom, Prenom:" << endl;
        cin >> name1 >> name2;
         j = chercher(name1, name2, admins);
        if(j != -1){
           admins[j]->AugmentationSalaireParAnnee();
           admins[j]->afficher();
        }
        else{
            j = chercher(name1, name2, enseignants);
             if( j != -1){
                enseignants[j]->AugmentationSalaireParAnnee();
                enseignants[j]->afficher();
            }
            else{
                cout << "Ce Personne N'existe Pas" << endl;
            }
        }
        break;
    case 3:
        cout << "Modification Du Salaire A:" << endl;
        cout << "Nom, Prenom:" << endl;
        cin >> name1 >> name2;
        cout << "Entrer Le Salaire:" << endl;

        cin >> salaire;
         j = chercher(name1, name2, admins);
        if(j != -1){
           admins[j]->updateSalary(salaire);
           admins[j]->afficher();
        }
        else{
            j = chercher(name1, name2, enseignants);
             if( j != -1){
                enseignants[j]->updateSalary(salaire);
                enseignants[j]->afficher();
            }
            else{
                cout << "Ce Personne N'existe Pas" << endl;
            }
        }
        break;
    case 4:
        cout << "Avertissement D'un Etudiant:" << endl;
         cout << "Nom, Prenom:" << endl;
        cin >> name1 >> name2;
        j = chercher(name1, name2, etudiants);
        if(j != -1){
           admins[j]->avertissement(*etudiants[j]);
        }
        else{
            cout << "L'etudiant N'existe Pas" << endl;
        }
        break;
    case 5:
        cout << "Donner Un Bonus A Un Etudiant" << endl;
        cout << "Nom, Prenom:" << endl;
        cin >> name1 >> name2;
         j = chercher(name1, name2, etudiants);
        if(j != -1){
           admins[j]->bonus(*etudiants[j]);
        }
        else{
            cout << "L'etudiant N'existe Pas" << endl;
        }
        break;
    case 6:
        cout << "Prendre Des Vacances" << endl;
          cout << "Nom, Prenom:" << endl;
        cin >> name1 >> name2;
        cout << "Entrer Le Nombre Des Jours:" << endl;
        cin >> nombre;

        j = chercher(name1, name2, admins);
        if(j != -1){
           admins[j]->prendreVacances(nombre);
        }
        else{
            j = chercher(name1, name2, enseignants);
             if( j != -1){
                enseignants[j]->prendreVacances(nombre);
            }
            else{
                cout << "Ce Personne N'existe Pas" << endl;
            }
        }
        break;
    case 7:
        cout << "Affichage Les Admins:" << endl;
        afficher(admins);
        break;
    case 8:
        cout << "Affichage Les Enseignants:" << endl;
        afficher(enseignants);
        break;
    case 9:
        cout << "Affichage Les Etudiants:" << endl;
        afficher(etudiants);
        break;
    case 10:
     cout << "Affichage Les Groupes:" << endl;
        afficher(groupes);
        break;
    case 11:
     cout << "Affichage Les Matieres:" << endl;
        afficher(matieres);
        break;
    case 12:
    cout << "Affichage De:" << endl;
     cout << "Nom, Prenom:" << endl;
        cin >> name1 >> name2;

         j = chercher(name1, name2, admins);
        if(j != -1){
           cout << "Admin:" << endl;
           admins[j]->afficher();
        }
        else{
            j = chercher(name1, name2, enseignants);
             if( j != -1){
               cout<<" Enseignant:"<< endl;
                enseignants[j]->afficher();
            }
            else{
                j = chercher(name1, name2, etudiants);
                if( j != -1){
               cout<<" Etudiant:"<< endl;
                etudiants[j]->afficher();
            }
            else{
                cout << "ce Personne N'existe Pas" << endl;}
            }
        }
        break;

    case 13:
cout <<"Niveau, Numero:" << endl;
        cin >> name1 >> nombre;
       j = chercher(name1, nombre, groupes);
             if( j != -1){
               cout <<"Nombre De Validation:" << groupes[j]->nbValidation() << endl;
            }
            else{
                cout << "Ce Personne N'existe Pas" << endl;
            }

        break;
    case 14:

        cin >> admin;
        admins.push_back(&admin);
        admin.afficher();
        break;

    case 15:
        cin >> ens;
        enseignants.push_back(&ens);
        ens.afficher();
        break;
    case 16:
         cin >> etud;
        etudiants.push_back(&etud);
        etud.afficher();
        break;
    case 17:
         cin >> grp;
        groupes.push_back(&grp);
        grp.afficher();
        break;
    case 18:
         cin >> mat;
        matieres.push_back(&mat);
        mat.afficher();
        break;
    case 19:
        cout<<"Nom Et Prenom D'etudiant:" << endl;
        cin >> name1 >> name2;
        j = chercher(name1, name2, etudiants);
        if( j != -1){
            del.setNom(etudiants[j]->getNom());
            del.setPrenom(etudiants[j]->getPrenom());
            del.setAge(etudiants[j]->getAge());
            del.setNumeroTele(etudiants[j]->getNumeroTele());
            del.setIdEtudiant(etudiants[j]->getIdEtudiant());
            del.setNiveau(etudiants[j]->getNiveau());
            del.setAnneeInscription(etudiants[j]->getAnneeInscription());
            del.setNotes(etudiants[j]->getNotes());
            del.setAbsence(etudiants[j]->getAbsence());
            del.setMatieres(etudiants[j]->getMatieres());
             cin >> del;
        delegues.push_back(&del);
        del.afficher();
        }
        else{
        cout<<"Etudiant N'existe Pas"<<endl;
        }
        break;
    case 20:
         cout << "Matiere:" << endl;
        cin >> matt;
        cout << "Nom, Prenom:" << endl;
        cin >> name1 >> name2;
        j = chercher(name1, name2, enseignants);
        if( j != -1){
         i = chercher(matt, matieres);
         if( i == -1){
            mat.setNom(matt);
            mat.setEnseignantResp(enseignants[j]);
            matieres.push_back(&mat);

         }
         else{
            matieres[i]->setEnseignantResp(enseignants[j]);
         }
         enseignants[j]->ajouterMatiere(matt);
         enseignants[j]->afficher();
        }
        else{
            cout << "Enseignant N'exist Pas" << endl;
        }
        break;
    case 21:      
        cout << "Niveau, Numero:" << endl;
        cin >> name1 >> nombre;

          cout << "Matiere:" << endl;
        cin >> matt;
        j = chercher(name1, nombre, groupes);
        if( j != -1){
         i = chercher(matt, matieres);
         if( i == -1){
            mat.setNom(matt);
            mat.setEnseignantResp(nullptr);
            matieres.push_back(&mat);
         }

         groupes[j]->ajouterMatiere(&mat);
         groupes[j]->afficher();
         for(size_t z = 0; z < groupes[j]->getEtudiants().size(); z++){
            groupes[j]->getEtudiants()[z]->ajouterMatiere(matt, 0);
         }
        }
        else{
            cout << "Groupe N'exist Pas" << endl;
        }
        break;
    case 22:
          cout << "Niveau:" << endl;
        cin >> matt;
        cout << "Nom, Prenom:" << endl;
        cin >> name1 >> name2;
        j = chercher(name1, name2, enseignants);
        if( j != -1){
         enseignants[j]->assignerNiveau(matt);
         enseignants[j]->afficher();
        }
        else{
            cout << "Enseignant N'exist Pas" << endl;
        }
        break;
    case 23:
        cout << "Nom, Prenom:" << endl;
        cin >> name1 >> name2;
        cout << "Niveau, Numero:" << endl;
        cin >> name3 >> nombre;

        i = chercher(name1, name2, etudiants);
        j = chercher(name3, nombre, groupes);
       if(i != -1){
         if(j != -1){
            groupes[j]->ajouterEtudiant(etudiants[i]);
            groupes[j]->afficher();
         }
         else
         {cout << "Groupe N'exist Pas" << endl;}
       }
       else
      { cout << "Etudiant N'exist Pas" << endl;}

        break;
    case 24:
        cout << "Nom De Matiere" << endl;
        cin >> name1;
        i = chercher(name1, matieres);
        for(size_t z = 0; z < enseignants.size(); z++){
            enseignants[z]->supprimerMatiere(name1);
        }
if(i != -1){
        for(size_t z = 0; z < groupes.size(); z++){
            groupes[z]->supprimerMatiere(matieres[i]);
            for(size_t k = 0; k < groupes[z]->getEtudiants().size(); k++){
                groupes[z]->getEtudiants()[k]->supprimerMatiere(name1);
            }
        }
        }
        supprimer(name1, matieres);
        break;
    case 25:
         cout << "Nom de matiere" << endl;
        cin >> name1;
         cout << "Nom Et Prenom De L'enseignant" << endl;
        cin >> name2 >> name3;

        i = chercher(name2,name3, enseignants);
        if(i != -1){
            enseignants[i]->supprimerMatiere(name1);
            enseignants[i]->afficher();
        }
      else{
        cout << "Enseignant N'exist Pas" << endl;
      }

        break;
    case 26:
         cout << "Nom de Matiere" << endl;
        cin >> name1;
         cout << "Niveau, Numero" << endl;
        cin >> name2 >> nombre;
        i = chercher(name2, nombre, groupes);
        if(i != -1){
            j = chercher(name1, matieres);
            if(j != -1){
                groupes[i]->supprimerMatiere(matieres[j]);
                groupes[i]->afficher();
            }

        }else
        {cout << "Groupe N'exist Pas" << endl;}

        break;
    case 27:
        cout << "Niveau, Numero" << endl;
        cin >> name2 >> nombre;
        i = chercher(name2, nombre, groupes);
        if(i != -1){
            groupes[i]->supprimerMatieres();
            groupes[i]->afficher();
        }
        else
        {cout << "Groupe N'exist Pas" << endl;}
        break;
    case 28:
         cout << "Niveau:" << endl;
        cin >> matt;
        cout << "Nom, Prenom:" << endl;
        cin >> name1 >> name2;
        j = chercher(name1, name2, enseignants);
        if( j != -1){
            enseignants[j]->supprimerNiveau(matt);
            enseignants[j]->afficher();
        }
        else{
            cout << "Enseignant N'exist Pas" << endl;
        }
        break;
    case 29:
        cout << "Niveau, Numero:" << endl;
        cin >> name1 >> nombre;
        cout << "Nom, Prenom:" << endl;
        cin >> name2 >> name3;

        j = chercher(name2, name3, etudiants);
        i = chercher(name1, nombre, groupes);
        if( i != -1){
            if(j != -1){
                groupes[i]->supprimerEtudiant(etudiants[j]);
                groupes[i]->afficher();
            }
            else{
                cout << "Etudiant N'exist Pas" << endl;
            }
        }
        else{
            cout << "Groupe N'exist Pas" << endl;
        }
        break;
    case 30:
         cout << "Niveau, Numero:" << endl;
        cin >> name1 >> nombre;
        i = chercher(name1, nombre, groupes);
        if( i != -1){
            groupes[i]->supprimerEtudiants();
            groupes[i]->afficher();
        }
         else{
            cout << "Groupe N'exist Pas" << endl;
        }
        break;
    case 31:
        cout << "Niveau, Numero:" << endl;
        cin >> name1 >> nombre;
        cout <<"Id: " << endl;
        cin >> name2;
        i = chercher(name1, nombre, groupes);
        if( i != -1){
            groupes[i]->supprimerEtudiantParId(name2);
            groupes[i]->afficher();
        }
         else{
            cout << "Groupe N'exist Pas" << endl;
        }
        break;
    case 32:
        cout << "Niveau Et Numero De Groupe:" << endl;
        cin >> name1 >> nombre;
        i = chercher(name1, nombre, groupes);
        if( i != -1){
            groupes[i]->supprimerEtudiantParNiveau();
            groupes[i]->afficher();
        }
         else{
            cout << "Groupe N'exist Pas" << endl;
        }
        break;
    case 33:
         cout << "Niveau Et Numero De Groupe:" << endl;
        cin >> name1 >> nombre;
        cout <<"Moyenne: " << endl;
        cin >> salaire;
        i = chercher(name1, nombre, groupes);
        if( i != -1){
            groupes[i]->supprimerEtudiantParMoyenne(salaire);
            groupes[i]->afficher();
        }
         else{
            cout << "Groupe N'exist Pas" << endl;
        }
        break;
    case 34:
        cout << "Quitter" << endl;
        break;
    default:
        cout << "Choix Invalide" << endl;
        break;
   }
   }

}
else{
    cout << "Mot De Passe Incorrect" << endl;
}
   }
   else if(choix == 2){
cout << "mode enseignant" << endl;
cout << "entrer le mot de passe" << endl;
cin >> mp;
if(mp == motdepasse){
    while(choix2 != 26){

     cout << "*************************"<< endl;
   cout << "Menu:" << endl;

   cout << "1.Prendre Vacances" << endl;
   cout << "2.Afficher les admins" << endl;
   cout << "3.Afficher les enseignants" << endl;
   cout << "4.Afficher les Etudiants" << endl;
   cout << "5.Afficher les groupes" << endl;
   cout << "6.Afficher un groupe" << endl;
   cout << "7.Afficher les matieres" << endl;
   cout << "8.Afficher specifiquement" << endl;
   cout << "9.Afficher le nombre de validation dans un groupe" << endl;
   cout << "10.Afficher moyenne d'un etudiant" << endl;
   cout << "11.Afficher resultat final d'un etudiant" << endl;
   cout << "12.Afficher l'absence total d'un etudiant" << endl;
   cout << "13.Afficher moyenne d'un groupe" << endl;
   cout << "14.Ajouter Un delegue a un groupe" << endl;
   cout << "15.Ajouter Une date d'examen" << endl;
   cout << "16.Ajouter Une Tache a un delegue" << endl;
   cout << "17.Supprimer date d'examen" << endl;
   cout << "18.Supprimer date d'examen par matiere" << endl;
   cout << "19.Supprimer Une Tache d'un delegue" << endl;
   cout << "20.Supprimer tous les Taches d'un delegue" << endl;
   cout << "21.Supprimer les Taches completes d'un delegue" << endl;
   cout << "22.Incrementer l'absence d'un etudiant" << endl;
   cout << "23.Evaluer un delegue" << endl;
   cout << "24.Planifier un evenement" << endl;
   cout << "25.Changer delegue" << endl;
   cout << "26.Quitter" << endl;
   cout << "votre choix:"<< endl;
   cout << "*************************"<< endl;
   cin >> choix2;

   switch (choix2)
   {

    case 1:
        cout << "prendre des vacances" << endl;
          cout << "nom:" << endl;
        cin >> name1;
        cout << "prénom:" << endl;
        cin >> name2;
        cout << "Entrer le nombre des jours:" << endl;
        cin >> nombre;

        j = chercher(name1, name2, admins);
        if(j != -1){
           admins[j]->prendreVacances(nombre);
        }
        else{
            j = chercher(name1, name2, enseignants);
             if( j != -1){
                enseignants[j]->prendreVacances(nombre);
            }
            else{
                cout << "ce personne n'existe pas" << endl;
            }
        }
        break;
    case 2:
        cout << "Affichage les admins:" << endl;
        afficher(admins);
        break;
    case 3:
        cout << "Affichage les enseignants:" << endl;
        afficher(enseignants);
        break;
    case 4:
        cout << "Affichage les Etudiants:" << endl;
        afficher(etudiants);
        break;
    case 5:
     cout << "Affichage les groupes:" << endl;
        afficher(groupes);
        break;
    case 6:
    cout <<"Niveau:" << endl;
        cin >> name1;
        cout <<"Numero:" << endl;
        cin >> nombre;
        j = chercher(name1, nombre, groupes);
        if(j != -1){
           groupes[j]->afficher();
        }
        else{
            cout << "ce groupe n'existe pas" << endl;
        }
    break;
    case 7:
     cout << "Affichage les matieres:" << endl;
        afficher(matieres);
        break;

    case 8:
    cout << "Affichage de:" << endl;
     cout << "nom:" << endl;
        cin >> name1;
        cout << "prénom:" << endl;
        cin >> name2;

         j = chercher(name1, name2, admins);
        if(j != -1){
           cout << "admin" << endl;
           admins[j]->afficher();
        }
        else{
            j = chercher(name1, name2, enseignants);
             if( j != -1){
               cout<<" enseignant"<< endl;
                enseignants[j]->afficher();
            }
            else{
                j = chercher(name1, name2, etudiants);
                if( j != -1){
               cout<<" etudiant"<< endl;
                etudiants[j]->afficher();
            }
            else{
                cout << "ce personne n'existe pas" << endl;}
            }
        }
        break;

    case 9:
cout <<"Niveau:" << endl;
        cin >> name1;
        cout <<"Numero:" << endl;
        cin >> nombre;
       j = chercher(name1, nombre, groupes);
             if( j != -1){
               cout <<"Nombre de validation:" << groupes[j]->nbValidation() << endl;
            }
            else{
                cout << "ce groupe n'existe pas" << endl;
            }

        break;

    case 10:
    cout <<"Nom:" << endl;
        cin >> name1;
        cout <<"Prenom:" << endl;
        cin >> name2;
       j = chercher(name1, name2, etudiants);
   if(j != -1)
   {
    cout << "Moyenne:" << etudiants[j]->moyenne() << endl;
   }
   else
   {cout << "Etudiant n'existe pas" << endl;}

    break;
     case 11:
    cout <<"Nom:" << endl;
        cin >> name1;
        cout <<"Prenom:" << endl;
        cin >> name2;
       j = chercher(name1, name2, etudiants);
   if(j != -1)
   {
    if(etudiants[j]->resultatFinale())
    {cout << "Valide" << endl;}
    else
    {cout << "Non valide" << endl;}
   }
   else
   {cout << "Etudiant n'existe pas" << endl;}

    break;

     case 12:
    cout <<"Nom:" << endl;
        cin >> name1;
        cout <<"Prenom:" << endl;
        cin >> name2;
       j = chercher(name1, name2, etudiants);
   if(j != -1)
   {
    cout << "Absence total:" << etudiants[j]->absenceTotal() << endl;
   }
   else
   {cout << "Etudiant n'existe pas" << endl;}

    break;
     case 13:
cout <<"Niveau:" << endl;
        cin >> name1;
        cout <<"Numero:" << endl;
        cin >> nombre;
       j = chercher(name1, nombre, groupes);
             if( j != -1){
               cout <<"Moyenne general:" << groupes[j]->moyenne() << endl;
            }
            else{
                cout << "ce groupe n'existe pas" << endl;
            }

        break;
    case 14:
        cout<<"Nom de delegue (nom, prenom):" << endl;
        cin >> name1 >> name2;
        
        cout<<"Groupe (niveau, numero):" << endl;
        cin >> name3 >> nombre;
        j = chercher(name1, name2, delegues);
        i =chercher(name3, nombre, groupes);
        if( j != -1){
            if(i != -1){
            groupes[i]->setDelegue(delegues[j]);
            groupes[i]->afficher();
            }
            else{
                 cout<<"groupe n'existe pas"<<endl;
            }
            
        }
        else{
        cout<<"delegue n'existe pas"<<endl;
        }
        break;

    case 15:
         cout << "matiere:" << endl;
        cin >> matt;
        cout << "Date(day, month, year):" << endl;
        cin >> d1.day >> d1.month >> d1.year;
        cout << "groupe (niveau, numero):" << endl;
        cin >> name1 >> nombre;
        j = chercher(name1, nombre, groupes);
        i = chercher(matt, matieres);
        if( j != -1){
         if( i != -1){
       groupes[j]->ajouterDateExamen(d1, matieres[i]);
       groupes[j]->afficher();
        }
        else{
            cout << "materie n'exist pas" << endl;
        }}else{
            cout << "groupe n'exist pas" << endl;
        }
        break;
    case 16:
           cout << "delegue (nom, prenom):" << endl;
        cin >> name1 >> name2;

        cout << "tache:" << endl;
        cin >> name3;

        j = chercher(name1, name2, delegues);
        if( j != -1){
        delegues[j]->ajouterTache(name3);
        delegues[j]->afficher();
        }
        else{
            cout << "delegue n'exist pas" << endl;
        }
        break;
    case 17:
          cout << "date:" << endl;
        cin >> d1.day >> d1.month >> d1.year;

        cout << "group (niveau, numero):" << endl;
        cin >> name1 >> nombre;

        j = chercher(name1, nombre, groupes);
        if( j != -1){
         groupes[j]->supprimerDateExamen(d1);
        groupes[j]->afficher();
        }
        else{
            cout << "Groupe n'exist pas" << endl;
        }
        break;
    case 18:
        cout << "matiere:" << endl;
        cin >> matt;

        cout << "group (niveau, numero):" << endl;
        cin >> name1 >> nombre;

        j = chercher(name1, nombre, groupes);
        i = chercher(matt, matieres);
        if( j != -1){
         if( i != -1){
        groupes[j]->supprimerDateExamen(matieres[i]);
        groupes[j]->afficher();
        }
        else{
            cout << "materie n'exist pas" << endl;
        }}else{
            cout << "groupe n'exist pas" << endl;
        }
        break;
    case 19:
         cout << "delegue (nom, prenom):" << endl;
        cin >> name1 >> name2;

        cout << "tache:" << endl;
        cin >> name3;

        j = chercher(name1, name2, delegues);
        if( j != -1){
        delegues[j]->supprimerTache(name3);
        delegues[j]->afficher();
        }
        else{
            cout << "delegue n'exist pas" << endl;
        }
        break;
    case 20:
          cout << "delegue (nom, prenom):" << endl;
        cin >> name1 >> name2;

        j = chercher(name1, name2, delegues);
        if( j != -1){
        delegues[j]->supprimerTaches();
        delegues[j]->afficher();
        }
        else{
            cout << "delegue n'exist pas" << endl;
        }
        break;
    case 21:
           cout << "delegue (nom, prenom):" << endl;
        cin >> name1 >> name2;

        j = chercher(name1, name2, delegues);
        if( j != -1){
        delegues[j]->supprimerTachesComplete();
        delegues[j]->afficher();
        }
        else{
            cout << "delegue n'exist pas" << endl;
        }
        break;
    case 22:
        cout << "Etudiant (nom, prenom):" << endl;
        cin >> name1 >> name2;

        cout << "matiere:" << endl;
        cin >> name3;

        i = chercher(name1, name2, etudiants);
        if(i != -1){
            etudiants[i]->incrementerAbsence(name3);
            etudiants[i]->afficher();
        }
        else
        {cout << "Etudiant n'exist pas" << endl;}
        break;
    case 23:
         cout << "Delegue (nom, prenom):" << endl;
        cin >> name1 >> name2;
        j = chercher(name1, name2, delegues);
        if( j != -1){
            delegues[j]->evaluation();
        }
        else{
            cout << "Delegue n'exist pas" << endl;
        }
        break;
    case 24:
        cout << "Groupe (niveau, numero):" << endl;
        cin >> name1 >> nombre;
        cout << "date (year, month, day):" << endl;
        cin >> d1.year >> d1.month >> d1.day;
        i = chercher(name1, nombre, groupes);
        if( i != -1){
        groupes[i]->planifierEvenement(d1);
        }
        else{
            cout << "Groupe n'exist pas" << endl;
        }
        break;
    case 25:
        cout << "Groupe (niveau, numero):" << endl;
        cin >> name1 >> nombre;
        i = chercher(name1, nombre, groupes);
        if( i != -1){
        groupes[i]->changerDelegue();
        }
        else{
            cout << "Groupe n'exist pas" << endl;
        }
        break;
    case 26:
        cout << "quitter" << endl;
        break;
    default:
        cout << "choix invalide" << endl;
        break;
   }
   }

}
else{
    cout << "mot de passe incorrect" << endl;
}
   }
     else if(choix == 3){
        cout << "mode delegue" << endl;
        x =-1;
 while(choix2 != 9){

     while(x == -1){
     cout <<"Votre nom" <<endl;
     cin >> name;
     cout <<"Votre prenom" <<endl;
     cin >> lastName;
     x = chercher(name, lastName, delegues);

     if(x == -1){
        cout << "vous n'etes pas delegue" << endl;
     }else{
        j =chercherGroupeParEtudiant(name, lastName, groupes);
     }
        }
     cout << "*************************"<< endl;
   cout << "Menu:" << endl;

   cout << "1.Afficher les enseignants de votre groupe" << endl;
   cout << "2.Afficher les Etudiants de votre groupe" << endl;
   cout << "3.Afficher les information de votre groupe" << endl;
   cout << "4.Afficher les matieres de votre groupe" << endl;
   cout << "5.Ajouter Une Tache" << endl;
   cout << "6.Evaluer un delegue" << endl;
   cout << "7.Planifier un evenement" << endl;
   cout << "8.completer un tache" << endl;
   cout << "9.Quitter" << endl;
   cout << "votre choix:"<< endl;
   cout << "*************************"<< endl;
   cin >> choix2;

   switch (choix2)
   {
    case 1:
        cout << "Affichage les enseignants:" << endl;

       for(size_t z = 0; z < groupes[j]->getMatieres().size(); z++){
        cout << groupes[j]->getMatieres()[z]->getEnseignantRespNom() << endl;
       }
        break;
    case 2:
        cout << "Affichage les Etudiants:" << endl;
          for(size_t z = 0; z < groupes[j]->getEtudiants().size(); z++){
        cout << groupes[j]->getEtudiants()[z]->getNom() << " " << groupes[j]->getEtudiants()[z]->getPrenom() << endl;
       }
        break;
    case 3:
     cout << "Affichage le groupe:" << endl;
        groupes[j]->afficher();
        break;
    case 4:
     cout << "Affichage les matieres:" << endl;
          for(size_t z = 0; z < groupes[j]->getMatieres().size(); z++){
        cout << groupes[j]->getMatieres()[z]->getNom() << endl;
       }
        break;
    case 5:
        cout << "tache:" << endl;
        cin >> name3;
        delegues[x]->ajouterTache(name3);
        delegues[x]->afficher();
        break;

    case 6:
            delegues[x]->evaluation();
        break;
    case 7:
        cout << "date (year, month, day):" << endl;
        cin >> d1.year >> d1.month >> d1.day;
        groupes[j]->planifierEvenement(d1);

        break;
          case 8:
        cout << "tache:" << endl;
        cin >> name3;
        delegues[x]->completerTache(name3);

        break;
    case 9:
        cout << "quitter" << endl;
        break;
    default:
        cout << "choix invalide" << endl;
        break;
   }
   }

   }
     else if(choix == 4){
        cout << "mode etudiant" << endl;
        x =-1;
 while(choix2 != 7){

     while(x == -1){
     cout <<"Votre nom" <<endl;
     cin >> name;
     cout <<"Votre prenom" <<endl;
     cin >> lastName;
     x = chercher(name, lastName, etudiants);

     if(x == -1){
        cout << "vous n'etes pas un etudiant" << endl;
     }else{
        j =chercherGroupeParEtudiant(name, lastName, groupes);
        groupes[j]->afficher();
     }
        }
     cout << "*************************"<< endl;
   cout << "Menu:" << endl;

   cout << "1.Afficher votre informations" << endl;
   cout << "2.Afficher votre notes et absence" << endl;
   cout << "3.Afficher les enseignants de votre groupe" << endl;
   cout << "4.Afficher les Etudiants de votre groupe" << endl;
   cout << "5.Afficher les information de votre groupe" << endl;
   cout << "6.Afficher les matieres de votre groupe" << endl;
   cout << "7.Quitter" << endl;
   cout << "votre choix:"<< endl;
   cout << "*************************"<< endl;
   cin >> choix2;

   switch (choix2)
   {
   case 1:
        cout << "Affichage de votre information:" << endl;

       etudiants[x]->afficher();
        break;
    case 2:
        cout << "Affichage de votre notes:" << endl;

       etudiants[x]->afficherNotes();
        break;
    case 3:
        cout << "Affichage des enseignants:" << endl;

       for(size_t z = 0; z < groupes[j]->getMatieres().size(); z++){
        cout << groupes[j]->getMatieres()[z]->getEnseignantResp()->getNom() << " " << groupes[j]->getMatieres()[z]->getEnseignantResp()->getPrenom() << endl;
       }
        break;
    case 4:
        cout << "Affichage des Etudiants:" << endl;
          for(size_t z = 0; z < groupes[j]->getEtudiants().size(); z++){
        cout << groupes[j]->getEtudiants()[z]->getNom() << " " << groupes[j]->getEtudiants()[z]->getPrenom() << endl;
       }
        break;
    case 5:
     cout << "Affichage le groupe:" << endl;
        groupes[j]->afficher();
        break;
    case 6:
     cout << "Affichage les matieres:" << endl;
          for(size_t z = 0; z < groupes[j]->getMatieres().size(); z++){
        cout << groupes[j]->getMatieres()[z]->getNom() << endl;
       }
        break;
    case 7:
        cout << "quitter" << endl;
        break;
    default:
        cout << "choix invalide" << endl;
        break;
   }
   }

   }
     else if(choix != 5){
    cout <<"choix invalide" << endl;
   }
 }
    return 0;
}

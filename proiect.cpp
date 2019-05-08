#include <iostream>
#include <math.h>

using namespace std;

class pereche {
    int grad;
    double coef;
    pereche *urm;
public:
    pereche();
    void setCoef(double);
    double getCoef();
    void setGrad(int);
    int getGrad();
    pereche *getUrm();
    void setUrm (pereche *x);
    void operator=(const pereche&);
    pereche operator*(const pereche&);
    pereche operator+(const pereche&);
    pereche operator-(const pereche&);
    pereche operator/(const pereche&);
    bool operator==(const pereche&);
    bool operator!=(const pereche&);
    friend istream& operator>>(istream& in, pereche &ob);
    friend ostream& operator<<(ostream& out, pereche &ob);
    friend class polinom;
};

bool pereche::operator==(const pereche &ob){
    if (this->grad==ob.grad && this->coef==ob.coef){
        return true;
    }
    return false;
}

bool pereche::operator!=(const pereche &ob){
    if (this->grad!=ob.grad && this->coef!=ob.coef){
        return false;
    }
    return true;
}

pereche::pereche(){
    this->coef=0;
    this->grad=0;
    this->urm=NULL;
}

istream& operator>>(istream& in, pereche &ob){
    cout<<"Introduceti gradul: ";
    in>>ob.grad;
    cout<<"\nIntroduceti coeficientul gradului "<<ob.grad<<": ";
    in>>ob.coef;
    return in;
}

ostream& operator<<(ostream& out, pereche &ob){
    out<<"+("<<ob.getCoef()<<'x'<<'^'<<ob.getGrad()<<')';
    return out;
}

pereche pereche::operator+(const pereche &ob){
    pereche per;
    per.coef=ob.coef+this->coef;
    per.grad=ob.grad;
    return per;
}

pereche pereche::operator-(const pereche &ob){
    pereche per;
    per.coef=abs(this->coef-ob.coef);
    per.grad=ob.grad;
    return per;
}

void pereche::operator= (const pereche &ob){
    this->coef=ob.coef;
    this->grad=ob.grad;
}

pereche pereche::operator* (const pereche &ob){
    pereche aux;
    aux.coef=this->coef*ob.coef;
    aux.grad=this->grad+ob.grad;
    return aux;
}

pereche pereche::operator/ (const pereche &ob){
    pereche aux;
    aux.grad=this->grad-ob.grad;
    aux.coef=this->coef/ob.coef;
    return aux;
}

void pereche::setCoef(double x){
    this->coef=x;
}

double pereche::getCoef(){
    return this->coef;
}

void pereche::setGrad(int x){
    this->grad=x;
}

int pereche::getGrad(){
    return this->grad;
}

pereche* pereche::getUrm(){
    return this->urm;
}

void pereche::setUrm (pereche *x){
    this->urm=x;
}

class polinom {
    pereche *start;
public:
    polinom();
    polinom(polinom &);
    ~polinom();
    void adauga (pereche);
    int eliminaZerouri();
    int calculValoare (int);
    void operator=(const polinom &ob);
    polinom operator+(const polinom &ob);
    polinom operator-(const polinom &ob);
    polinom operator*(const polinom &ob);
    pereche operator[](const int &index);
    polinom operator/(const polinom &ob);
    polinom operator%(const polinom &ob);
    bool operator==(const polinom&);
    bool operator!=(const polinom&);
    friend istream& operator>>(istream& in, polinom &ob);
    friend ostream& operator<<(ostream& out, polinom &ob);
    friend class pereche;
};

bool polinom::operator==(const polinom &ob){
    pereche *p1, *p2;
    p1=this->start;
    p2=ob.start;
    while (p1!=NULL && p2!=NULL){
        if (*p1!=*p2){
            return false;
        }
        p1=p1->urm;
        p2=p2->urm;
    }
    if (p1!=NULL || p2!=NULL){
        return false;
    }
    return true;
}

bool polinom::operator!=(const polinom &ob){
    pereche *p1, *p2;
    p1=this->start;
    p2=ob.start;
    while (p1!=NULL && p2!=NULL){
        if (*p1==*p2){
            return false;
        }
        p1=p1->urm;
        p2=p2->urm;
    }
    if (p1!=NULL || p2!=NULL){
        return false;
    }

    return true;
}

polinom::polinom(){
    this->start=NULL;
}

polinom::polinom (polinom &ob){
    pereche *start, *aux, *t, *parcurge;
    start=new pereche;
    polinom rasp;
    rasp.start=start;
    (*start).coef=(*ob.start).coef;
    (*start).grad=(*ob.start).grad;
    (*start).urm=NULL;
    t=start;
    parcurge=(*ob.start).urm;
    while (parcurge!=NULL){
        aux=new pereche;
        (*t).urm=aux;
        (*aux).grad=(*parcurge).grad;
        (*aux).coef=(*parcurge).coef;
        (*aux).urm=NULL;
        t=aux;
        parcurge=(*parcurge).urm;
    }
    this->start=rasp.start;
}

int polinom::calculValoare(int x){
    pereche *aux=this->start;
    int suma=0;
    while (aux!=NULL){
        int gr=(*aux).grad;
        double cf=(*aux).coef;
        int val=1;
        while (gr!=0){
            val=val*x;
            gr--;
        }
        suma+=(val*cf);
        aux=(*aux).urm;
    }
    return suma;
}

istream& operator>>(istream& in, polinom &ob){
    cout<<"Introduceti numarul de monoame: ";
    int n;
    in>>n;
    for (int i=1; i<=n; i++){
        pereche x;
        cin>>x;
        ob.adauga(x);
    }
    ob.eliminaZerouri();
    return in;
}

ostream& operator<<(ostream& out, polinom &ob){
    pereche *x = ob.start;
    while (x != NULL){
        cout<<(*x);
        x = (*x).getUrm();
    }
    return out;
}
/*
void polinom::operator=(const polinom &ob){
    pereche *start, *aux, *t, *parcurge;
    start=new pereche;
    polinom rasp;
    rasp.start=start;
    (*start).coef=(*ob.start).coef;
    (*start).grad=(*ob.start).grad;
    (*start).urm=NULL;
    t=start;
    parcurge=(*ob.start).urm;
    while (parcurge!=NULL){
        aux=new pereche;
        (*t).urm=aux;
        (*aux).grad=(*parcurge).grad;
        (*aux).coef=(*parcurge).coef;
        (*aux).urm=NULL;
        t=aux;
        parcurge=(*parcurge).urm;
    }
    this->start=rasp.start;
}
*/
void polinom::operator=(const polinom &ob){
    this->start=NULL;
    pereche *parcurge;
    parcurge=ob.start;
    while (parcurge!=NULL){
        this->adauga(*parcurge);
        parcurge=parcurge->urm;
    }
}

polinom polinom::operator+(const polinom &ob){
    polinom raspuns;
    pereche *parcurs1=this->start;
    pereche *parcurs2=ob.start;
    while (parcurs1!=NULL && parcurs2!=NULL){
        if ((*parcurs1).grad<(*parcurs2).grad){
            raspuns.adauga(*parcurs2);
            parcurs2=(*parcurs2).urm;
        }
        else{
            if ((*parcurs2).grad<(*parcurs1).grad){
                raspuns.adauga(*parcurs1);
                parcurs1=(*parcurs1).urm;
            }
            else{
                raspuns.adauga(*(parcurs1) + *(parcurs2) );
                parcurs1=(*parcurs1).urm;
                parcurs2=(*parcurs2).urm;
            }
        }
    }

    while (parcurs1!=NULL){
        raspuns.adauga(*parcurs1);
        parcurs1=(*parcurs1).urm;
    }

    while (parcurs2!=NULL){
        raspuns.adauga(*parcurs2);
        parcurs2=(*parcurs2).urm;
    }

    return raspuns;
}

polinom polinom::operator-(const polinom &ob){
    polinom raspuns,pol1,pol2;
    pol1=(*this);
    pol2=ob;
    pereche *parcurs1=pol1.start;
    pereche *parcurs2=pol2.start;
    while (parcurs1!=NULL && parcurs2!=NULL){
        if ((*parcurs1).grad<(*parcurs2).grad){
            (*parcurs2).coef=-(*parcurs2).coef;
            raspuns.adauga(*parcurs2);
            parcurs2=(*parcurs2).urm;
        }
        else{
            if ((*parcurs2).grad<(*parcurs1).grad){
                raspuns.adauga(*parcurs1);
                parcurs1=(*parcurs1).urm;
            }
            else{
                raspuns.adauga((*parcurs1) - (*parcurs2));
                parcurs1=(*parcurs1).urm;
                parcurs2=(*parcurs2).urm;
            }
        }
    }

    if (raspuns.eliminaZerouri()==0){
        polinom raspuns1;
        pereche a;
        a.grad=0;
        a.coef=0;
        raspuns1.adauga(a);
        return raspuns1;
    }

    pereche *aux;

    while (parcurs1!=NULL){
        aux=parcurs1;
        (*aux).coef=(*aux).coef;
        raspuns.adauga(*parcurs1);
        parcurs1=(*parcurs1).urm;
    }

    while (parcurs2!=NULL){
        aux=parcurs2;
        (*aux).coef=-(*aux).coef;
        raspuns.adauga(*parcurs2);
        parcurs2=(*parcurs2).urm;
    }

    return raspuns;
}

polinom polinom::operator*(const polinom &ob){
    polinom raspuns, polAux;
    if (this->start==NULL || ob.start==NULL){
        cout<<"Inmultire cu polinomul nul";
        pereche aux;
        aux.coef=0;
        aux.grad=0;
        aux.urm=NULL;
        raspuns.adauga(aux);
        return raspuns;
    }
    pereche *parcurs1=this->start;
    pereche *parcurs2=ob.start;
    pereche aux;
    aux.coef=0;
    aux.grad=0;
    aux.urm=NULL;
    raspuns.adauga(aux);

    while (parcurs1!=NULL){
        parcurs2=ob.start;
        polAux.start=NULL;
        while (parcurs2!=NULL){
            polAux.adauga( (*parcurs1)*(*parcurs2) );
            parcurs2=(*parcurs2).urm;
        }
        raspuns=raspuns+polAux;
        parcurs1=(*parcurs1).urm;
    }
    raspuns.eliminaZerouri();
    return raspuns;
}

polinom polinom::operator/(const polinom &ob){
    polinom polinom1, polinom2, rasp;
    polinom1=*this;
    polinom2=ob;
    if ((*polinom1.start).grad < (*polinom2.start).grad){
        pereche *aux;
        (*aux).grad=0;
        (*aux).coef=0;
        cout<<'0';
        rasp.start=aux;
        return rasp;
    }
    pereche aux;
    aux=(*polinom1.start)/(*polinom2.start);
    while ((*polinom1.start).grad >= (*polinom2.start).grad){
        rasp.adauga(aux);
        polinom polinom3;
        polinom3.adauga(aux);
        polinom3=polinom3*polinom2;
        polinom1=polinom1-polinom3;
        if (polinom1.start!=NULL){
            aux=(*polinom1.start)/(*polinom2.start);
        }
    }
    return rasp;
}

polinom polinom::operator%(const polinom &ob){
    if ( this->start->grad < (*ob.start).grad){
        return *this;
    }
    if ( (*ob.start).coef==0 ){
        cout<<"Impartire cu polinomul nul";
        polinom x;
        x=ob;
        return x;
    }
    polinom a;
    a=(*this)/ob;
    polinom b;
    b=(a*ob);
    polinom rasp;
    rasp=(*this)-b;
    return rasp;
}

int polinom::eliminaZerouri(){
    pereche *aux=this->start;
    while ((*aux).coef==0 && aux!=NULL){
        if ((*aux).urm==NULL){
            cout<<"Polinomul obtinut in urma eliminarii zerourilor (posibil sa apara acest mesaj pe parcursul operatiei) este nul\n";
            return 0;
        }
        aux=(*aux).urm;
    }

    this->start=aux;
    aux=aux->urm;

    pereche *undeSeAdauga=this->start;

    while (aux!=NULL){
        if ((*aux).coef!=0){
            undeSeAdauga->urm=aux;
            undeSeAdauga=undeSeAdauga->urm;
        }
        if ((*aux).urm==NULL && (*aux).coef==0){
            undeSeAdauga->urm=NULL;
        }
        aux=aux->urm;
    }

    return 1;
}

void polinom::adauga (pereche deAdaugat){
    if (this->start == NULL){
        pereche *prim = new pereche;
        prim->coef = deAdaugat.getCoef();
        prim->grad = deAdaugat.getGrad();
        prim->urm = NULL;
        this->start = prim;
    }
    else {
        pereche *aux = this->start;
        if (deAdaugat.getGrad() > (*aux).getGrad()){
            pereche *prim = new pereche;
            prim->coef = deAdaugat.getCoef();
            prim->grad = deAdaugat.getGrad();
            prim->urm = this->start;
            this->start = prim;
        }
        else{
            while (aux->urm != NULL){
                if ( ( (*aux).getGrad() > deAdaugat.getGrad() && (*aux->urm).getGrad() < deAdaugat.getGrad() ) ){
                    pereche *add = new pereche;
                    add->coef = deAdaugat.getCoef();
                    add->grad = deAdaugat.getGrad();
                    add->urm = (*aux).getUrm();
                    (*aux).setUrm(add);
                    return;
                }
                aux = (*aux).getUrm();
            }
            pereche *add = new pereche;
            add->coef = deAdaugat.getCoef();
            add->grad = deAdaugat.getGrad();
            add->urm = NULL;
            (*aux).setUrm(add);
        }
    }
}

polinom::~polinom(){
    pereche *aux, *ant;
    aux=this->start;
    ant=this->start;
    while (aux!=NULL){
        aux=aux->urm;
        delete ant;
        ant=aux;
    }
}

pereche polinom::operator[] (const int &index){
    pereche *aux=this->start;
    int contor=1;
    while (contor<index && aux!=NULL){
        aux=(*aux).urm;
        contor++;
    }
    if (aux==NULL){
        cout<<"Eroare!";
        pereche a;
        a.coef=0;
        a.grad=0;
        return a;
    }
    else{
        return *aux;
    }
}

int main () {
    polinom a,b,c;
    pereche per;
    cout<<"Introduceti datele polinomului a:\n";
    cin>>a;
    cout<<"Introduceti datele polinomului b:\n";
    cin>>b;
    int nrIntrodus=1;
    while(nrIntrodus!=0){
        cout<<"\nMENIU\n0)Exit;\n1)a+b;\n2)a-b;\n3)a*b;\n4)a/b;\n5)a%b;\n6)a[];\n7)b[];\nIntroduceti numarul dorit:";
        cin>>nrIntrodus;
        if (nrIntrodus==0){
            break;
        }
        if (nrIntrodus==1){
            c=a+b;
            cout<<c;
        }
        if (nrIntrodus==2){
            c=a-b;
            cout<<c;
        }
        if (nrIntrodus==3){
            c=a*b;
            cout<<c;
        }
        if (nrIntrodus==4){
            c=a/b;
            cout<<c;
        }
        if (nrIntrodus==5){
            c=a%b;
            cout<<c;
        }
        if (nrIntrodus==6){
            cout<<"Introduceti indicele: ";
            int k;
            cin>>k;
            pereche x=a[k];
            cout<<x;
        }
        if (nrIntrodus==7){
            cout<<"Introduceti indicele: ";
            int k;
            cin>>k;
            pereche x=b[k];
            cout<<x;
        }
    }
    return 0;
}

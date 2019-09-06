#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ag.h"
#include "vector"

using namespace std;


int nGeracoes;
struct cidade resposta[TAMCROMOSSOMO];
vector <float> melhor;
vector <float> vetorMedia;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QwtPlot plot;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCalcular_clicked()
{

        struct cidade capitais[27] = {{"Aracaju",0,463,191},{"Belem",1,337,86},{"Belo Horizonte",2,380,296},{"Boa Vista",3,197,37},{"Brasilia",4,344,250},{"Campo Grande",5,264,309},{"Cuiaba",6,247,242},{"Curitiba",7,327,357},{"Florianopolis",8,335,382},{"Fortaleza",9,452,114},{"Goiania",10,328,267},{"Joao Pessoa",11,489,155},{"Macapa",12,305,68},{"Maceio",13,473,181},{"Manaus",14,204,102},{"Natal",15,484,134},{"Palmas",16,341,176},{"Porto Alegre",17,306,412},{"Porto Velho",18,160,166},{"Recife",19,486,165},{"Rio Branco",20,112,180},{"Rio de Janeiro",21,393,325},{"Salvador",22,447,213},{"Sao Luis",23,384,100},{"Sao Paulo",24,349,337},{"Teresina",25,404,132},{"Vitoria",26,424,302}};
        struct cidade populacao[TAMPOPULACAO][TAMCROMOSSOMO];
        struct cidade populacaoFilhos[TAMPOPULACAO][TAMCROMOSSOMO];
        float avaliacoes[TAMPOPULACAO];
        struct cidade filho1[TAMCROMOSSOMO],filho2[TAMCROMOSSOMO];
        srand(time(NULL));
        int nCruzamento,nMutacao;
        nGeracoes = ui->edGeracoes->text().toInt();
        nCruzamento = ui->edCruzamentos->text().toInt();
        nMutacao = ui->edMutacao->text().toInt();
        int i;
        int pMelhor;
        float media;
        iniciaPopulacao(populacao,capitais);

        for(int g=1;g<=nGeracoes;g++){

            ui->progressBar->setValue(g);
            fazAvaliacoes(populacao,avaliacoes);


        i=0;
        pMelhor = achaPosicaoMelhor(avaliacoes);
        melhor.push_back(avaliacoes[pMelhor]);
        vetorMedia.push_back(calculaMedia(avaliacoes));
        copiaCromossomo(populacaoFilhos[i],populacao[pMelhor]);
        i++;
        do{
            int pai1 = torneio(avaliacoes,3);
            int pai2 = torneio(avaliacoes,3);
            if(rand()%(nCruzamento+nMutacao) <nCruzamento){
                cruzamento(populacao[pai1],populacao[pai2],filho1,filho2);
            }else{
                mutacao(populacao[pai1],filho1);
                mutacao(populacao[pai2],filho2);
            }
            copiaCromossomo(populacaoFilhos[i],filho1);
            i++;
            if(i<TAMPOPULACAO){
                copiaCromossomo(populacaoFilhos[i],filho2);
                i++;
            }
        }while(i<TAMPOPULACAO);
        copiaPopulacao(populacao,populacaoFilhos);

        }
        fazAvaliacoes(populacao,avaliacoes);
        pMelhor = achaPosicaoMelhor(avaliacoes);
        imprimeCromo(populacao[pMelhor]);
        printf("\n numero %d",pMelhor);
        printf("\n A distancia percorrida foi de %.2f",
              avaliacoes[pMelhor]);
        ui->pushButton->setEnabled(true);
}


void MainWindow::on_edCruzamentos_editingFinished()
{
  int c = ui->edCruzamentos->text().toInt();
  int m = 100 - c;
  ui->edMutacao->setText(QString::number(m));
}

void MainWindow::on_edMutacao_editingFinished()
{
    int m = ui->edMutacao->text().toInt();
    int c = 100 - m;
    ui->edCruzamentos->setText(QString::number(c));
}

void MainWindow::on_pushButton_clicked()
{

    plot.setTitle( "Melhores x Média");
    plot.setCanvasBackground( Qt::white );

    plot.insertLegend( new QwtLegend() );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( &plot );

    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setTitle( "Melhor" );
    curve->setPen( Qt::blue, 4 );

    QwtPlotCurve *curve2 = new QwtPlotCurve();
    curve2->setTitle( "Média" );
    curve2->setPen( Qt::red, 4 );

    //curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    //Pontos da curva
    //QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
    //    QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    //curve->setSymbol( symbol );

    QPolygonF points;
    for(int i=0;i<melhor.size();i++)
        points << QPointF(i,melhor.at(i));

    QPolygonF points2;
    for(int i=0;i<vetorMedia.size();i++)
        points2 << QPointF(i,vetorMedia.at(i));


   curve->setSamples( points );
   curve2->setSamples( points2 );

    curve->attach( &plot );
    curve2->attach(&plot);

    plot.resize( 600, 400 );
    plot.replot();
    plot.show();








}

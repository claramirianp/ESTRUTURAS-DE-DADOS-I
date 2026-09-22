CREATE DATABASE BDEQUIPE;
USE BDEQUIPE;

CREATE TABLE Treinador(
	cpf VARCHAR(15),
    nome VARCHAR(80),
    historico VARCHAR(200),
    dataNasc DATE,
    salario INT,
    PRIMARY KEY(cpf)
);

CREATE TABLE Jogador(
	cpf VARCHAR(15),
    nome VARCHAR(80),
    nick VARCHAR(20),
    funcao VARCHAR(20),
    statusJ VARCHAR(20),
    genero VARCHAR(10),
    data_nasc DATE,
    salario INT,
    gols INT,
    assistencias INT, 
    mvps INT,
    defesas INT,
    PRIMARY KEY(cpf)
);

CREATE TABLE Treinamento(
	jogador VARCHAR(15),
    treinador VARCHAR(15),
    dataTreino DATE,
    PRIMARY KEY(jogador, treinador),
    FOREIGN KEY(jogador) REFERENCES Jogador(cpf),
    FOREIGN KEY(treinador) REFERENCES Treinador(cpf)
);

CREATE TABLE Contrato(
	id INT AUTO_INCREMENT,
    data_ini DATE,
    data_fim DATE,
    clausulas VARCHAR(200),
    statusC VARCHAR(10),
    treinador VARCHAR(15),
    jogador VARCHAR(15),
    PRIMARY KEY(id),
    FOREIGN KEY(treinador) REFERENCES Treinador(cpf),
    FOREIGN KEY(jogador) REFERENCES Jogador(cpf)
);

CREATE TABLE Despesas(
	id INT AUTO_INCREMENT,
    dataDes DATE,
    valor INT,
    origem VARCHAR(100),
    PRIMARY KEY(id)
);

CREATE TABLE Saude(
	dataSaude DATE,
    medico VARCHAR(80),
    especialidade VARCHAR(50),
    diagnostico VARCHAR(200),
    motivo VARCHAR(100),
    jogador VARCHAR(15),
    PRIMARY KEY(dataSaude),
    FOREIGN KEY(jogador) REFERENCES Jogador(cpf)
);

CREATE TABLE Partida(
	dataPart DATE,
    hora TIME,
    resultado VARCHAR(10),
    duracao FLOAT,
    liga VARCHAR(30),
    modalidade VARCHAR(20),
    PRIMARY KEY(dataPart)
);

CREATE TABLE Viagem(
	id INT AUTO_INCREMENT,
    statusViag VARCHAR(10),
    destino VARCHAR(30),
    motivo VARCHAR(80),
    transporte VARCHAR(20),
    hospedagem VARCHAR(50),
    PRIMARY KEY(id)
);

CREATE TABLE Faz(
	dataFaz DATE,
    jogador VARCHAR(15),
    viagem INT,
    PRIMARY KEY(dataFaz, jogador, viagem),
    FOREIGN KEY(jogador) REFERENCES Jogador(cpf),
    FOREIGN KEY(viagem) REFERENCES Viagem(id)
);

CREATE TABLE Joga(
	jogador VARCHAR(15),
    partida DATE,
    gols INT,
    assistencias INT,
    mvps INT,
    defesas INT,
    PRIMARY KEY(jogador, partida),
    FOREIGN KEY(jogador) REFERENCES Jogador(cpf),
    FOREIGN KEY(partida) REFERENCES Partida(dataPart)
);

CREATE TABLE Gera(
	despesa INT,
    treinador VARCHAR(15),
    jogador VARCHAR(15),
    viagem INT,
    saude DATE,
    PRIMARY KEY(despesa, treinador, jogador, viagem, saude),
    FOREIGN KEY(despesa) REFERENCES Despesas(id),
    FOREIGN KEY(treinador) REFERENCES Treinador(cpf),
    FOREIGN KEY(jogador) REFERENCES Jogador(cpf),
    FOREIGN KEY(viagem) REFERENCES Viagem(id),
    FOREIGN KEY(saude) REFERENCES Saude(dataSaude)
);

INSERT INTO Treinador VALUES
	('111.111.111-11','Carlos Henrique','Ex-jogador profissional de Rocket League','1982-03-15',12000),
	('222.222.222-22','Marcos Silva','Especialista em estratégia ofensiva','1985-07-20',11500),
	('333.333.333-33','Juliana Costa','Treinadora de categorias de base','1990-01-12',9500),
	('444.444.444-44','Ricardo Souza','Coach tático internacional','1987-09-02',13000),
	('555.555.555-55','Fernanda Lima','Especialista em análise de desempenho','1991-05-18',10000);

INSERT INTO Jogador VALUES
	('100.000.000-01','Lucas Almeida','Luk','Atacante','Ativo','Masculino','2001-02-10',8500,215,180,42,95),
	('100.000.000-02','Pedro Henrique','PH','Defensor','Ativo','Masculino','2000-05-17',8300,98,145,25,320),
	('100.000.000-03','Gabriel Souza','Gabs','Ala','Ativo','Masculino','2002-07-14',8100,180,160,31,180),
	('100.000.000-04','João Vitor','JV','Atacante','Ativo','Masculino','1999-11-08',9000,240,175,55,90),
	('100.000.000-05','Matheus Lima','MTH','Defensor','Ativo','Masculino','2001-09-28',8400,90,130,22,350),
	('100.000.000-06','Rafael Costa','Rafa','Ala','Ativo','Masculino','2000-04-16',8200,165,155,29,200),
	('100.000.000-07','Gustavo Rocha','Ghost','Atacante','Ativo','Masculino','2002-01-30',9100,260,185,60,85),
	('100.000.000-08','Felipe Martins','Flip','Defensor','Ativo','Masculino','1998-08-19',8600,105,170,30,330),
	('100.000.000-09','Bruno Oliveira','Brunex','Ala','Ativo','Masculino','2003-06-25',7900,150,140,28,175),
	('100.000.000-10','Diego Santos','DG','Atacante','Ativo','Masculino','2001-10-12',8800,225,160,47,105),
	('100.000.000-11','Thiago Lopes','TL','Defensor','Reserva','Masculino','2002-02-14',7000,70,90,14,220),
	('100.000.000-12','Vinicius Moraes','Vini','Ala','Reserva','Masculino','2000-12-03',7100,110,125,18,160),
	('100.000.000-13','Leonardo Silva','Leo','Atacante','Ativo','Masculino','1999-04-22',8700,205,175,39,100),
	('100.000.000-14','Caio Pereira','CP','Defensor','Ativo','Masculino','2001-03-09',8200,88,140,24,315),
	('100.000.000-15','Igor Mendes','Igor','Ala','Ativo','Masculino','2003-05-13',8000,155,150,27,195),
	('100.000.000-16','Amanda Ferreira','Amy','Atacante','Ativo','Feminino','2002-08-01',8500,210,168,44,120),
	('100.000.000-17','Larissa Gomes','Lari','Defensor','Ativo','Feminino','2001-01-18',8400,92,155,21,305),
	('100.000.000-18','Beatriz Alves','Bia','Ala','Reserva','Feminino','2000-06-27',7600,120,138,20,175),
	('100.000.000-19','Nicole Rocha','Nick','Atacante','Ativo','Feminino','2003-11-11',8300,185,158,36,118),
	('100.000.000-20','Camila Souza','Kami','Defensor','Ativo','Feminino','2002-09-21',8100,95,145,26,298);
    
INSERT INTO Treinamento VALUES
	('100.000.000-01','111.111.111-11','2025-01-10'),
	('100.000.000-02','111.111.111-11','2025-01-10'),
	('100.000.000-03','111.111.111-11','2025-01-11'),
	('100.000.000-04','111.111.111-11','2025-01-11'),
	('100.000.000-05','222.222.222-22','2025-01-12'),
	('100.000.000-06','222.222.222-22','2025-01-12'),
	('100.000.000-07','222.222.222-22','2025-01-13'),
	('100.000.000-08','222.222.222-22','2025-01-13'),
	('100.000.000-09','333.333.333-33','2025-01-14'),
	('100.000.000-10','333.333.333-33','2025-01-14'),
	('100.000.000-11','333.333.333-33','2025-01-15'),
	('100.000.000-12','333.333.333-33','2025-01-15'),
	('100.000.000-13','444.444.444-44','2025-01-16'),
	('100.000.000-14','444.444.444-44','2025-01-16'),
	('100.000.000-15','444.444.444-44','2025-01-17'),
	('100.000.000-16','444.444.444-44','2025-01-17'),
	('100.000.000-17','555.555.555-55','2025-01-18'),
	('100.000.000-18','555.555.555-55','2025-01-18'),
	('100.000.000-19','555.555.555-55','2025-01-19'),
	('100.000.000-20','555.555.555-55','2025-01-19');
    
INSERT INTO Contrato(data_ini,data_fim,clausulas,statusC,treinador,jogador) VALUES
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','111.111.111-11','100.000.000-01'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','111.111.111-11','100.000.000-02'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','111.111.111-11','100.000.000-03'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','111.111.111-11','100.000.000-04'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','222.222.222-22','100.000.000-05'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','222.222.222-22','100.000.000-06'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','222.222.222-22','100.000.000-07'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','222.222.222-22','100.000.000-08'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','333.333.333-33','100.000.000-09'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','333.333.333-33','100.000.000-10'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Reserva','333.333.333-33','100.000.000-11'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Reserva','333.333.333-33','100.000.000-12'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','444.444.444-44','100.000.000-13'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','444.444.444-44','100.000.000-14'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','444.444.444-44','100.000.000-15'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','444.444.444-44','100.000.000-16'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','555.555.555-55','100.000.000-17'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Reserva','555.555.555-55','100.000.000-18'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','555.555.555-55','100.000.000-19'),
	('2025-01-01','2026-12-31','Contrato padrão de atleta','Ativo','555.555.555-55','100.000.000-20');
    
INSERT INTO Partida VALUES
	('2025-02-01','19:00:00','3x1',5.2,'RLCS SAM','Rocket League'),
	('2025-02-08','20:00:00','3x2',6.1,'RLCS SAM','Rocket League'),
	('2025-02-15','18:30:00','1x3',4.8,'RLCS SAM','Rocket League'),
	('2025-02-22','21:00:00','3x0',4.5,'Copa Brasil','Rocket League'),
	('2025-03-01','20:30:00','3x2',5.7,'Copa Brasil','Rocket League'),
	('2025-03-08','19:30:00','2x3',6.0,'RLCS SAM','Rocket League'),
	('2025-03-15','18:00:00','3x1',5.3,'RLCS SAM','Rocket League'),
	('2025-03-22','20:00:00','3x0',4.6,'Masters','Rocket League'),
	('2025-03-29','19:00:00','2x3',5.8,'Masters','Rocket League'),
	('2025-04-05','21:00:00','3x1',5.4,'Masters','Rocket League');
    
INSERT INTO Viagem(statusViag,destino,motivo,transporte,hospedagem) VALUES
	('Concluída','São Paulo','RLCS SAM','Avião','Hotel Ibis'),
	('Concluída','Rio de Janeiro','Copa Brasil','Avião','Hotel Windsor'),
	('Concluída','Curitiba','Bootcamp','Ônibus','Hotel Slaviero'),
	('Agendada','Brasília','Masters','Avião','Hotel Nacional'),
	('Agendada','Belo Horizonte','Evento Promocional','Van','Hotel Mercure');
    
INSERT INTO Joga VALUES
	('100.000.000-01','2025-02-01',2,1,1,3),
	('100.000.000-02','2025-02-01',0,2,0,8),
	('100.000.000-03','2025-02-01',1,1,0,5),
	('100.000.000-04','2025-02-08',2,0,1,2),
	('100.000.000-05','2025-02-08',0,1,0,9),
	('100.000.000-06','2025-02-08',1,2,0,4),
	('100.000.000-07','2025-02-15',1,0,0,3),
	('100.000.000-08','2025-02-15',0,1,0,10),
	('100.000.000-09','2025-02-15',0,2,1,6),
	('100.000.000-10','2025-02-22',3,0,1,2),
	('100.000.000-01','2025-02-22',0,2,0,4),
	('100.000.000-02','2025-02-22',0,1,0,7),
	('100.000.000-03','2025-03-01',1,2,1,5),
	('100.000.000-04','2025-03-01',2,0,0,3),
	('100.000.000-05','2025-03-01',0,1,0,8),
	('100.000.000-06','2025-03-08',1,1,0,4),
	('100.000.000-07','2025-03-08',0,0,0,9),
	('100.000.000-08','2025-03-08',1,2,1,7),
	('100.000.000-09','2025-03-15',2,1,1,4),
	('100.000.000-10','2025-03-15',1,1,0,5),
	('100.000.000-01','2025-03-15',0,2,0,6),
	('100.000.000-02','2025-03-22',1,2,1,8),
	('100.000.000-03','2025-03-22',2,0,0,4),
	('100.000.000-04','2025-03-22',0,1,0,5),
	('100.000.000-05','2025-03-29',1,1,0,9),
	('100.000.000-06','2025-03-29',0,2,0,8),
	('100.000.000-07','2025-03-29',1,0,1,3),
	('100.000.000-08','2025-04-05',2,1,1,6),
	('100.000.000-09','2025-04-05',0,2,0,5),
	('100.000.000-10','2025-04-05',1,0,0,4);
    
INSERT INTO Faz VALUES
	('2025-01-28','100.000.000-01',1),
	('2025-01-28','100.000.000-02',1),
	('2025-01-28','100.000.000-03',1),
	('2025-01-28','100.000.000-04',1),
	('2025-02-18','100.000.000-05',2),
	('2025-02-18','100.000.000-06',2),
	('2025-02-18','100.000.000-07',2),
	('2025-02-18','100.000.000-08',2),
	('2025-03-10','100.000.000-09',3),
	('2025-03-10','100.000.000-10',3),
	('2025-03-10','100.000.000-11',3),
	('2025-03-10','100.000.000-12',3),
	('2025-03-25','100.000.000-13',4),
	('2025-03-25','100.000.000-14',4),
	('2025-03-25','100.000.000-15',4),
	('2025-03-25','100.000.000-16',4),
	('2025-04-10','100.000.000-17',5),
	('2025-04-10','100.000.000-18',5),
	('2025-04-10','100.000.000-19',5),
	('2025-04-10','100.000.000-20',5);
    
INSERT INTO Saude VALUES
	('2025-01-20','Dr. Ricardo Mendes','Fisioterapia','Recuperação muscular','Treino intenso','100.000.000-01'),
	('2025-01-22','Dra. Ana Carolina','Ortopedia','Entorse leve no punho','Dor durante treino','100.000.000-04'),
	('2025-02-05','Dr. Felipe Oliveira','Oftalmologia','Fadiga ocular','Excesso de telas','100.000.000-07'),
	('2025-02-18','Dra. Mariana Costa','Nutrição','Readequação alimentar','Avaliação periódica','100.000.000-10'),
	('2025-03-03','Dr. Gustavo Almeida','Psicologia','Controle emocional','Preparação para campeonato','100.000.000-13'),
	('2025-03-10','Dra. Beatriz Rocha','Fisioterapia','Alongamento preventivo','Avaliação física','100.000.000-16'),
	('2025-03-20','Dr. Eduardo Martins','Ortopedia','Dor cervical','Postura inadequada','100.000.000-19'),
	('2025-04-02','Dra. Juliana Ferreira','Nutrição','Acompanhamento nutricional','Rotina esportiva','100.000.000-20');
    
INSERT INTO Despesas(dataDes,valor,origem) VALUES
	('2025-01-18',3500,'Compra de periféricos'),
	('2025-01-28',6800,'Passagens aéreas'),
	('2025-02-10',2200,'Hospedagem'),
	('2025-02-18',950,'Consultas médicas'),
	('2025-03-01',1800,'Alimentação da equipe'),
	('2025-03-12',4200,'Bootcamp'),
	('2025-03-25',7600,'Viagem campeonato'),
	('2025-04-01',1200,'Uniformes'),
	('2025-04-05',900,'Medicamentos'),
	('2025-04-10',5100,'Evento promocional');
    
INSERT INTO Gera VALUES
	(1,'111.111.111-11','100.000.000-01',1,'2025-01-20'),
	(2,'111.111.111-11','100.000.000-04',1,'2025-01-22'),
	(3,'222.222.222-22','100.000.000-07',2,'2025-02-05'),
	(4,'333.333.333-33','100.000.000-10',2,'2025-02-18'),
	(5,'444.444.444-44','100.000.000-13',3,'2025-03-03'),
	(6,'444.444.444-44','100.000.000-16',4,'2025-03-10'),
	(7,'555.555.555-55','100.000.000-19',5,'2025-03-20'),
	(8,'555.555.555-55','100.000.000-20',5,'2025-04-02');
    

SELECT * FROM Treinador;

SELECT * FROM Jogador;

SELECT * FROM Treinamento;

SELECT * FROM Contrato;

SELECT * FROM Despesas;

SELECT * FROM Saude;

SELECT * FROM Partida;

SELECT * FROM Viagem;

SELECT * FROM Faz;

SELECT * FROM Joga;

SELECT * FROM Gera;

-- 1. Jogador e seu treinador

SELECT j.nome AS jogador, j.nick, t.nome AS treinador
FROM Jogador j JOIN Treinamento tr ON j.cpf = tr.jogador
JOIN Treinador t ON tr.treinador = t.cpf;


-- 2. Jogador e seu contrato

SELECT j.nome AS jogador, c.data_ini, c.data_fim, c.statusC
FROM Jogador j JOIN Contrato c ON j.cpf = c.jogador;


-- 3. Jogadores que participaram das partidas

SELECT j.nome AS jogador, p.dataPart, p.resultado
FROM Jogador j JOIN Joga jo ON j.cpf = jo.jogador
JOIN Partida p ON jo.partida = p.dataPart;


-- 4. Jogadores que viajaram

SELECT j.nome AS jogador, v.destino, v.motivo
FROM Jogador j JOIN Faz f ON j.cpf = f.jogador
JOIN Viagem v ON f.viagem = v.id;


-- 5. Histórico de saúde dos jogadores

SELECT j.nome AS jogador, s.medico, s.especialidade, s.diagnostico
FROM Jogador j JOIN Saude s ON j.cpf = s.jogador;


-- 6. Despesas relacionadas aos jogadores

SELECT j.nome AS jogador, d.origem, d.valor
FROM Jogador j JOIN Gera g ON j.cpf = g.jogador
JOIN Despesas d ON g.despesa = d.id;


-- 7. Despesas relacionadas aos treinadores

SELECT t.nome AS jogador, d.origem, d.valor
FROM Treinador t JOIN Gera g ON t.cpf = g.treinador
JOIN Despesas d ON g.despesa = d.id;

-- DROP DATABASE BDEQUIPE;
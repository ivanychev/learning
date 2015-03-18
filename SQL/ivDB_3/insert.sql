set identity_insert city on
insert into city (city_id, name)
values (1, 'temp');
set identity_insert city off

set identity_insert university on
insert into university (uni_id, name, city_id)
values(1, 'temp', 1);
set identity_insert university off

set identity_insert team on
insert into team (team_id, name, uni_id)
values(1, 'temp', 1);
set identity_insert team off

set identity_insert competition on
insert into competition(comp_id, description)
values(1, 'temp');
set identity_insert competition off

set identity_insert person on
insert into person(person_id, first_name, last_name, birth_date, death_date, sex, uni_id)
values (1, 'temp', 'temp', '1/1/1900', '1/1/2000', 'm', 1);
set identity_insert person off

set identity_insert roles_description on 
insert into roles_description(role_id, description)
values (1, 'temp');
set identity_insert roles_description off

set identity_insert season on
insert into season(season_id, season_index, begin_date, end_date)
values(1, 1, '1/1/1900', '1/1/1901');
set identity_insert season off

set identity_insert league on
insert into league(league_id, name, upper_id)
values (1, 'temp', NULL);
set identity_insert league off

set identity_insert game on
insert into game(game_id, name, league_id, game_date, city_id, season_id, next_stage, place_to_next)
values(1, 'temp', 1, '1/1/1900', 1, 1, 1, 1);
set identity_insert game off

set identity_insert sponsor_description on
insert into sponsor_description(sponsor_id, description)
values (1, 'temp');
set identity_insert sponsor_description off

set identity_insert record_type on
insert into record_type(type_id, description, bitrate_kbps)
values(1, 'temp', 1);
set identity_insert record_type off

set identity_insert source on
insert into source(source_id, person_id, description)
values(1, 1, 'temp');
set identity_insert source off

set identity_insert record on
insert into record(rec_id, game_id, type_id, source_id, url)
values(1, 1, 1, 1, 'http://temp.ru');
set identity_insert record off

delete from record;
delete from source;
delete from record_type;
delete from sponsor_description;
delete from game;
delete from league;
delete from season;
delete from roles_description;
delete from person;
delete from competition;
delete from team;
delete from university;
delete from city;

ddb checkident (record,			reseed, 0);
ddb checkident (source,			reseed, 0);
ddb checkident (record_type,		reseed, 0);
ddb checkident (sponsor_description,	reseed, 0);	
ddb checkident (game,			reseed, 0);
ddb checkident (league,			reseed, 0);
ddb checkident (season,			reseed, 0);
ddb checkident (roles_description,	reseed, 0);	
ddb checkident (person,			reseed, 0);
ddb checkident (competition,		reseed, 0);
ddb checkident (team,			reseed, 0);
ddb checkident (university,		reseed, 0);
ddb checkident (city,			reseed, 0);



insert into city(name) values('Moscow');
insert into city(name) values('S.Petersburg');
insert into city(name) values('Kursk');
insert into city(name) values('Ekaterinburg');
insert into city(name) values('Vladivostok');
insert into city(name) values('Pyatigorsk');
insert into city(name) values('Sochi');
insert into city(name) values('Jurmala');
insert into city(name) values('Kiev');
insert into city(name) values('Minsk');
insert into city(name) values('Volgograd');
insert into city(name) values('Samara');


/*1 */insert into university(name, city_id) values('MGSU',1);
/*2 */insert into university(name, city_id) values('BGU',10); -- yes
/*3 */insert into university(name, city_id) values('SPbGU',2); -- yes
/*4 */insert into university(name, city_id) values('USGU',3); -- yes
/*5 */insert into university(name, city_id) values('EGU',4);
/*6 */insert into university(name, city_id) values('VGU',5);
/*7 */insert into university(name, city_id) values('PGU',6); -- yes
/*8 */insert into university(name, city_id) values('SGU',7); -- yes 
/*9 */insert into university(name, city_id) values('KGU',9); -- yes
/*10*/insert into university(name, city_id) values('MIPT',1);-- yes
/*11*/insert into university(name, city_id) values('MIEMP',1);
/*12*/insert into university(name, city_id) values('MIET',1);
/*13*/insert into university(name, city_id) values('VSE',1);  -- yes
/*14*/insert into university(name, city_id) values('MISIS',1);
/*15*/insert into university(name, city_id) values('MGUKI',1)
/*16*/insert into university(name, city_id) values('MGPU',1); -- yes
/*17*/insert into university(name, city_id) values('USTU',4); -- yes
/*18*/insert into university(name, city_id) values('MPI',1);  -- yes
/*19*/insert into university(name, city_id) values('VOLSU',11);  -- yes
/*20*/insert into university(name, city_id) values('SSU',11); -- yes


insert into team(name, uni_id) values('Stanciya Sportivnaya',16);
insert into team(name, uni_id) values('Uralskie pelmeni',17);
insert into team(name, uni_id) values('SMD 16 bit',13);
insert into team(name, uni_id) values('ChP',2);
insert into team(name, uni_id) values('Sbornaya SpB',3);
insert into team(name, uni_id) values('Prima',4);
insert into team(name, uni_id) values('Sbornaya Pyatigorska',7);
insert into team(name, uni_id) values('Utomlennue solncem',8);
insert into team(name, uni_id) values('Vinnickie percy',9);
insert into team(name, uni_id) values('Flood',10);
insert into team(name, uni_id) values('Sgushchenka',18);
insert into team(name, uni_id) values('SKK',7);
insert into team(name, uni_id) values('Z-side', NULL);
insert into team(name, uni_id) values('Vse puchkom',NULL);
insert into team(name, uni_id) values('Groza', NULL);
insert into team(name, uni_id) values('Tapki',19);
insert into team(name, uni_id) values('Sok',20);
insert into team(name, uni_id) values('Piramida',NULL);
insert into team(name, uni_id) values('Tumbler',NULL);
insert into team(name, uni_id) values('Sandali',NULL);
insert into team(name, uni_id) values('Uventus',2);


insert into competition(description) values('Privetstvie');
insert into competition(description) values('Freestyle');
insert into competition(description) values('Razminka');
insert into competition(description) values('Biatlon');
insert into competition(description) values('STEM');
insert into competition(description) values('Muz dz');
insert into competition(description) values('KOP');
insert into competition(description) values('Video concurs');


insert into person (first_name,last_name,sex, uni_id) values('Yuliy','Gusman', 'm', 8);
insert into person (first_name,last_name,sex, uni_id) values('Igor','Vernik', 'm', 3);
insert into person (first_name,last_name,sex, uni_id) values('KONstantin','Ernst', 'm', 6);
insert into person (first_name,last_name,sex, uni_id) values('LeONid','Yarmolnik', 'm', 1);
insert into person (first_name,last_name,sex, uni_id) values('Michail','Efremov', 'm', 2);
insert into person (first_name,last_name,sex, uni_id) values('Leonid','Yakubovich', 'm', 5);
insert into person (first_name,last_name,sex, uni_id) values('Dmitriy','Kojoma', 'm', 11);
insert into person (first_name,last_name,sex, uni_id) values('Ivan','Pushnenko', 'm', 11);
insert into person (first_name,last_name,sex, uni_id) values('Dmitriy','Brekotkin', 'm', 5);
insert into person (first_name,last_name,sex, uni_id) values('Alexander','Svetlakov', 'm', 5);
insert into person (first_name,last_name,sex, uni_id) values('Sergey','Sokolov', 'm', 5);
insert into person (first_name,last_name,sex, uni_id) values('Ilya','Aksenov', 'm', 1);
insert into person (first_name,last_name,sex, uni_id) values('Galya','Petrova', 'm', 1);
insert into person (first_name,last_name,sex, uni_id) values('Vadim','Frolov', 'm', 1);
insert into person (first_name,last_name,sex, uni_id) values('Evgeniy','Smorigin', 'm', 2);
insert into person (first_name,last_name,sex, uni_id) values('Dmitriy','Tankovich', 'm', 2);
insert into person (first_name,last_name,sex, uni_id) values('Dmitriy','Khrustalev', 'm', 3);
insert into person (first_name,last_name,sex, uni_id) values('Alexander','Yakushev', 'm', 4);
insert into person (first_name,last_name,sex, uni_id) values('Alexander','Kravcov', 'm', 4);
insert into person (first_name,last_name,sex, uni_id) values('Semen','Slepakov', 'm', 7);
insert into person (first_name,last_name,sex, uni_id) values('Elena','Borshcheva', 'f', 7);
insert into person (first_name,last_name,sex, uni_id) values('Evgeniy','Gordeev', 'm', 7);
insert into person (first_name,last_name,sex, uni_id) values('David','Muragyan', 'm', 7);
insert into person (first_name,last_name,sex, uni_id) values('Michail','Galustyan', 'm', 8);
insert into person (first_name,last_name,sex, uni_id) values('Alexander','Revva', 'm', 8);
insert into person (first_name,last_name,sex, uni_id) values('Elena','Rubalko', 'f', 8);
insert into person (first_name,last_name,sex, uni_id) values('Sergey','Lunin', 'm', 8);
insert into person (first_name,last_name,sex, uni_id) values('Dmitriy','Golubev', 'm', 9);
insert into person (first_name,last_name,sex, uni_id) values('Irina','SopONaru', 'f', 9);
insert into person (first_name,last_name,sex, uni_id) values('Oleg','Pashkovskiy', 'm', 9);
insert into person (first_name,last_name,sex, uni_id) values('Alexey','Balitskiy', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Ksenya','Chepurchenko', 'f', 10);
insert into person (first_name,last_name,sex, uni_id) values('Victor','Mishin', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Alexander','Kirushin', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Petr','Ivanov', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Kirill','Nekludov', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Natalie','Samoylova', 'f', 10);
insert into person (first_name,last_name,sex, uni_id) values('Mari','Ruskina', 'f', 10);
insert into person (first_name,last_name,sex, uni_id) values('Evginiy','Vyaluy', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Ivan','Yudintsev', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Alexander','Kostin', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Michail','Trofimov', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Evgeniy','Kapaev', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Artem','Papanov', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Alexey','Baydin', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Sergey','Dovgal', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Fedor','Gocharov', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Ivan','Kozicin', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Kais','Nofal', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Ivan','Shepitko', 'm', 10);
insert into person (first_name,last_name,sex, uni_id) values('Alexandra','Burashnikova', 'f', 10);
insert into person (first_name,last_name,sex, uni_id) values('Aigul','Zaidullina', 'f', 10);
insert into person (first_name,last_name,sex, uni_id) values('Bigaium','Tashmatova', 'f', 10);
insert into person (first_name,last_name,sex, uni_id) values('Elena','Tverdohlebova', 'f', 10);
insert into person (first_name,last_name,sex, uni_id) values('Ekaterina','Pavlova', 'f', 11);
insert into person (first_name,last_name,sex, uni_id) values('Vladimir','Postin', 'm', 11);
insert into person (first_name,last_name,sex, uni_id) values('Dorji','Mangataev', 'm', 12);
insert into person (first_name,last_name,sex, uni_id) values('Stanislav','Gayduk', 'm', 12);
insert into person (first_name,last_name,sex, uni_id) values('Vitaliy','Ivanuhin', 'm', 12);
insert into person (first_name,last_name,sex, uni_id) values('KONstantin','Baranov', 'm', 13);
insert into person (first_name,last_name,sex, uni_id) values('Andrey','Skiba', 'm', 13);
insert into person (first_name,last_name,sex, uni_id) values('Nikita','Dvornik', 'm', 14);
insert into person (first_name,last_name,sex, uni_id) values('Filipp','Orlov', 'm', 14);
insert into person (first_name,last_name,sex, uni_id) values('Ivan','Bukov', 'm', 14);
insert into person (first_name,last_name,sex, uni_id) values('Mariya','Golovanova', 'f', 15);
insert into person (first_name,last_name,sex, uni_id) values('Michail','Kiselev', 'm', 15);
insert into person (first_name,last_name,sex, uni_id) values('Yulia','Menshikova', 'f', 5); --367


insert into roles_description(description) values('player');
insert into roles_description(description) values('judge');
insert into roles_description(description) values('journalist');
insert into roles_description(description) values('presenter');
insert into roles_description(description) values('operator');

insert into season(begin_date, end_date, season_index) values ('10/2/2004', '20/2/2004', 29);
insert into season(begin_date, end_date, season_index) values ('11/2/2005', '15/2/2005', 30);
insert into season(begin_date, end_date, season_index) values ('11/2/2010', '23/2/2010', 35);


insert into league(name, upper_id) values('Vysshaya liga', NULL);
insert into league(name, upper_id) values('Premier liga', 1);


insert into roles(person_id, role_id, season_id, league_id, team_id) values()

1-13

--insert into roles(person_id, team_id, role_id, season_id, league_id) values(7,1, 1,'01/01/2004',NULL);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(7,1, 1, 1, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(7,1, 1, 2, 1);


--insert into roles(person_id, team_id, role_id, season_id, league_id) values(8,1, 1,'02/02/2004',NULL);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(8, 1, 1, 1, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(8, 1, 1, 2, 1);

-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(9,2, 1,'03/03/2004','02/03/2007');
insert into roles(person_id, team_id, role_id, season_id, league_id) values(9, 2, 1, 1, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(9, 2, 1, 2, 1);


--insert into roles(person_id, team_id, role_id, season_id, league_id) values(10,2, 1,'04/04/2004','02/05/2007');
insert into roles(person_id, team_id, role_id, season_id, league_id) values(10, 2, 1, 1, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(10, 2, 1, 2, 1);


--insert into roles(person_id, team_id, role_id, season_id, league_id) values(11,2, 1,'05/05/2004',NULL);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(11, 2, 1, 1, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(11, 2, 1, 2, 1);

-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(12,3, 1,'06/03/2004','05/07/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(13,3, 1,'05/02/2003','05/09/2007');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(14,3, 1,'05/01/2003','05/06/2006');
insert into roles(person_id, team_id, role_id, season_id, league_id) values(12, 3, 1, 1, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(12, 3, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(13,3,1, 1, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(13,3,1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(14,3,1, 1, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(14,3,1, 2, 1);


-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(15,4, 1,'05/02/2002','05/07/2006');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(16,4, 1,'05/03/2003',NULL);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(15, 4, 1, 1, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(15, 4, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(16, 4, 1, 1, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(16, 4, 1, 2, 1);


-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(17,5, 1,'05/02/2001','05/04/2007');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(18,6, 1,'07/04/2003','05/07/2007');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(19,6, 1,'03/03/2001','05/08/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(20,7, 1,'05/04/2003','05/07/2006');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(21,7, 1,'06/07/2004',NULL);
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(22,7, 1,'02/03/2003','05/05/2006');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(23,7, 1,'03/02/2002','05/06/2009');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(24,8, 1,'07/04/2004','05/08/2007');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(25,8, 1,'05/01/2001',NULL);
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(26,8, 1,'07/04/2002','05/08/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(27,8, 1,'06/01/2003',NULL);
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(28,9, 1,'08/03/2002','05/06/2009');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(29,9, 1,'09/08/2002','05/07/2006');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(30,9, 1,'05/03/2004','05/03/2005');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(31,10, 1,'03/04/2003','05/05/2005');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(32,10, 1,'02/01/2003','05/09/2009');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(33,10, 1,'04/02/2001','05/06/2009');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(34,10, 1,'06/04/2004',NULL);
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(35,11, 1,'02/03/2002','05/08/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(36,11, 1,'02/01/2004','05/09/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(37,11, 1,'01/02/2001','05/05/2007');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(38,12, 1,'06/03/2002','05/07/2009');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(39,12, 1,'05/04/2003',NULL);
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(40,13, 1,'05/01/2001',NULL);
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(41,13, 1,'07/03/2004','05/08/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(42,13, 1,'05/03/2004','05/08/2007');

insert into roles(person_id, team_id, role_id, season_id, league_id) values(17, 5, 1, 1, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(17, 5, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(18, 6, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(18, 6, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(19, 6, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(19, 6, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(20, 7, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(20, 7, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(21, 7, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(21, 7, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(22, 7, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(22, 7, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(23, 7, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(23, 7, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(24, 8, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(24, 8, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(25, 8, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(25, 8, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(26, 8, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(26, 8, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(27, 8, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(27, 8, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(28, 9, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(28, 9, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(29, 9, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(29, 9, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(30, 9, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(30, 9, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(31, 10, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(31, 10, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(32, 10, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(32, 10, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(33, 10, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(33, 10, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(34, 10, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(34, 10, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(35, 11, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(35, 11, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(36, 11, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(36, 11, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(37, 11, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(37, 11, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(38, 12, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(38, 12, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(39, 12, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(39, 12, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(40, 13, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(40, 13, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(41, 13, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(41, 13, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(42, 13, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) values(42, 13, 1, 2, 1);

-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(30,3, 1,'05/03/2005','05/03/2009');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(31,6, 1,'05/05/2005','05/05/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(44,5, 1,'05/05/2005','05/05/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(45,1, 1,'05/08/2005','05/08/2009');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(46,10, 1,'05/06/2006','05/06/2009');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(67,2, 1,'05/06/2006','05/06/2009');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(64,3, 1,'05/03/2002','05/08/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(65,9, 1,'05/06/2003','05/05/2007');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(66,13, 1,'04/01/2004','05/07/2009');

insert into roles(person_id, team_id, role_id, season_id, league_id) _values(30, 3, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(30, 3, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(31, 6, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(31, 6, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(44, 5, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(44, 5, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(45, 1, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(45, 1, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(46, 10, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(46, 10, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(67, 2, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(67, 2, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(64, 3, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(64, 3, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(65, 9, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(65, 9, 1, 2, 1);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(66, 13, 1, 1, 1); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(66, 13, 1, 2, 1);


insert into roles(person_id, team_id, role_id, season_id, league_id) values(43,14, 1,'05/01/2004','05/07/2007');
insert into roles(person_id, team_id, role_id, season_id, league_id) values(44,14, 1,'07/02/2003','05/05/2005');
insert into roles(person_id, team_id, role_id, season_id, league_id) values(45,14, 1,'04/04/2002','05/08/2005');
insert into roles(person_id, team_id, role_id, season_id, league_id) values(29,14, 1,'05/07/2006','05/07/2007');
insert into roles(person_id, team_id, role_id, season_id, league_id) values(46,15, 1,'05/04/2001','05/06/2006');
insert into roles(person_id, team_id, role_id, season_id, league_id) values(47,15, 1,'06/01/2004',NULL);
insert into roles(person_id, team_id, role_id, season_id, league_id) values(48,16, 1,'08/02/2002','05/08/2008');
insert into roles(person_id, team_id, role_id, season_id, league_id) values(49,16, 1,'09/01/2001','05/06/2009');
insert into roles(person_id, team_id, role_id, season_id, league_id) values(50,16, 1,'08/04/2003',NULL);


-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(51,17, 1,'08/02/2002','05/07/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(52,17, 1,'09/05/2004','05/07/2009');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(53,17, 1,'05/04/2004',NULL);
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(54,18, 1,'05/06/2001','05/08/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(55,18, 1,'04/02/2002','05/08/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(56,19, 1,'03/08/2002','05/07/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(57,19, 1,'05/08/2003','05/08/2009');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(58,20, 1,'02/04/2004','05/08/2007');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(59,20, 1,'01/06/2003',NULL);
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(60,20, 1,'05/03/2001','05/09/2009');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(61,21, 1,'07/06/2004','05/06/2009');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(62,21, 1,'05/02/2002','05/06/2008');
-- insert into roles(person_id, team_id, role_id, season_id, league_id) values(63,21, 1,'09/04/2001',NULL);

insert into roles(person_id, team_id, role_id, season_id, league_id) _values(51, 17, 1, 1, 2); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(51, 17, 1, 2, 2);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(52, 17, 1, 1, 2); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(52, 17, 1, 2, 2);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(53, 17, 1, 1, 2); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(53, 17, 1, 2, 2);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(54, 18, 1, 1, 2); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(54, 18, 1, 2, 2);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(55, 18, 1, 1, 2); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(55, 18, 1, 2, 2);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(56, 19, 1, 1, 2); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(56, 19, 1, 2, 2);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(57, 19, 1, 1, 2); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(57, 19, 1, 2, 2);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(58, 20, 1, 1, 2); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(58, 20, 1, 2, 2);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(59, 20, 1, 1, 2); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(59, 20, 1, 2, 2);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(60, 20, 1, 1, 2); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(60, 20, 1, 2, 2);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(61, 21, 1, 1, 2); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(61, 21, 1, 2, 2);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(62, 21, 1, 1, 2); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(62, 21, 1, 2, 2);
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(63, 21, 1, 1, 2); 
insert into roles(person_id, team_id, role_id, season_id, league_id) _values(63, 21, 1, 2, 2);




-- insert into city (name) VALUES ('Москва');
-- insert into city (name) VALUES ('Санкт-Петербург');
-- insert into city (name) VALUES ('Киев');
-- insert into city (name) VALUES ('Одесса');
-- insert into city (name) VALUES ('Минск');
-- insert into city (name) VALUES ('Алматы');
-- insert into city (name) VALUES ('Астана');
-- insert into city (name) VALUES ('Тольятти');
-- insert into city (name) VALUES ('Сухум');
-- insert into city (name) VALUES ('Баку');
-- insert into city (name) VALUES ('Бишкек');
-- insert into city (name) VALUES ('Рига');
-- insert into city (name) VALUES ('Улан-Удэ');
-- insert into city (name) VALUES ('Долгопрудный');
-- insert into city (name) VALUES ('Краснодар');
-- insert into city (name) VALUES ('Пятигорск');
-- insert into city (name) VALUES ('Днепропетровск');
-- insert into city (name) VALUES ('Камызяк');
-- insert into city (name) VALUES ('Тюмень');
-- insert into city (name) VALUES ('Ярославль'); 
-- insert into city (name) VALUES ('Казань'); 
-- insert into city (name) VALUES ('Сочи'); 
-- insert into city (name) VALUES ('Мурманск');
-- insert into city (name) VALUES ('Томск');
-- insert into city (name) VALUES ('Пенза');
-- insert into city (name) VALUES ('Воскресенское');
-- insert into city (name) VALUES ('Кемерово');
-- insert into city (name) VALUES ('Красноярск');
-- insert into city (name) VALUES ('Саратов');
-- insert into city (name) VALUES ('Энгельс');
-- insert into city (name) VALUES ('Махачкала');
-- insert into city (name) VALUES ('Бишкек');
-- insert into city (name) VALUES ('Грозный');
-- insert into city (name) VALUES ('Сургут');
-- insert into city (name) VALUES ('Ростов-на-Дону');
-- insert into city (name) VALUES ('Чита');
-- insert into city (name) VALUES ('Вязьма');
-- insert into city (name) VALUES ('Астрахань');
-- insert into city (name) VALUES ('Нягань');
-- insert into city (name) VALUES ('Иркутск');
-- insert into city (name) VALUES ('Пятигорск');
-- insert into city (name) VALUES ('Омск');
-- insert into city (name) VALUES ('Новосибирск');
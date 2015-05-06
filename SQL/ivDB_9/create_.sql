use ivKVN
SET DATEFORMAT dmy;

create table city (
	city_id int not null primary key identity(1, 1),
	name 	nvarchar(1000) not null
);

create table university (
	uni_id 	int not null primary key identity(1, 1),
	name 	nvarchar(1000) not null,
	city_id int references city (city_id)
				on delete no action
				on update cascade,
);


create table team (
	team_id	int not null primary key identity(1, 1),
	name 	nvarchar(1000) not null,
	uni_id 	int references university(uni_id)
				on delete no action
				on update cascade
);

create table competition (
	comp_id	int not null primary key identity(1, 1),
	description nvarchar(1000) not null 
);


create table person (
	person_id 	int 	  not null primary key  identity(1, 1),
	first_name 	nvarchar(100) not null,
	last_name	nvarchar(100) not null,
	sex 		nchar(1)  check( sex like 'm' 
					or 
					sex like 'f')
				  not null,
	uni_id 		int references university(uni_id)
				on delete no action
				on update cascade
);

create table roles_description (
	role_id 	int not null primary key  identity(1, 1),
	description 	nvarchar(1000) not null,
);

create table season (
	season_id 	int not null primary key  identity(1, 1),
	season_index 	int not null,
	begin_date 	datetime2 not null,
	end_date 	datetime2 not null
);

create table league (
	league_id 	int not null primary key  identity(1, 1),
	name 		nvarchar(1000) not null,
	upper_id 	int null references league(league_id)
				on delete no action
				on update no action
);

-- ^ Проблема с циклом на себя


create table roles (
	person_id 	int not null references person(person_id)
--				on update cascade
				,
	role_id  	int references roles_description(role_id) 
				on delete no action
				on update cascade 
				not null,
	season_id 	int references season(season_id)
				on delete no action
				on update cascade 
				not null,
	league_id 	int references league(league_id) 
				on delete no action
				on update cascade 
				not null,
	team_id 	int references team(team_id)     
				on delete set null
				on update cascade 
				null,
	primary key(person_id, season_id, league_id)
)

create table game (
	game_id 	int not null primary key  identity(1, 1),
	name 		nvarchar(1000),
	league_id 	int references league(league_id)
				on delete no action
				on update cascade ,
	game_date	datetime2,
	city_id  	int references city(city_id)
				on delete no action
				on update cascade ,
	season_id 	int references season(season_id)
				on delete no action
				on update cascade ,
	next_stage 	int references game(game_id)
				on delete no action
				on update no action,
	place_to_next 	int	
);


create table marks (
	team_id	int references team(team_id)
				on delete set null
				on update cascade ,
	game_id int not null references game(game_id)
				on delete no action
				on update no action,   -- cascade 
	comp_id int not null references competition(comp_id)
				on delete no action
				on update cascade ,
	jury_id int not null references person(person_id)
				on delete no action
				on update no action,   -- cascade
	score 	decimal(1,0) not null check(score >= 0),
	primary key (team_id, game_id, comp_id, jury_id)
);



create table sponsor_description (
	sponsor_id 	int not null primary key  identity(1, 1),
	description 	nvarchar(1000) not null
);

create table sponsor (
	sponsor_id 	int references sponsor_description(sponsor_id) 
				on delete no action
				on update cascade 
				not null,
	season_id 	int references season(season_id) 
				on delete no action
				on update cascade 
				not null,
	league_id 	int references league(league_id) 
				on delete no action
				on update cascade 
				not null,
	amount 		money,
	primary key(sponsor_id, season_id, league_id)
);

create table record_type (
	type_id 	int not null primary key  identity(1, 1),
	description 	nvarchar(1000),
	bitrate_kbps 	int check(bitrate_kbps is null
					or
				  bitrate_kbps > 0) null
);

create table source (
	source_id 	int not null primary key  identity(1, 1),
	person_id 	int references person(person_id)
				on delete no action
				on update cascade ,
	description 	nvarchar(1000) not null
);

create table record (
	rec_id 		int not null primary key  identity(1, 1),
	game_id 	int not null references game(game_id)
				on delete no action
				on update cascade ,
	type_id 	int not null references record_type(type_id)
				on delete no action
				on update cascade ,
	source_id 	int not null references source(source_id)
				on delete no action
				on update no action ,  -- cascade
	url 		nvarchar(1000) 
			check(url like 'http%'
				or
			      url like 'ftp%')
				  default('http://yandex.com')
);



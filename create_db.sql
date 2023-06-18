drop table if exists `boards`;
drop table if exists `games`;
drop table if exists `accounts`;

create table accounts (
	`id` int auto_increment,
	`username` varchar(255) unique not null,
	`password` varchar(255) not null,
	`key` varchar(255) not null,
	`date_created` datetime not null,
	primary key (`id`)
);

create table games (
	`id` int not null,
	`user_id` int not null,
	`empty_char` varchar(1) not null,
	`size` enum('4', '9', '16') not null,
	`difficulty` enum('E', 'M', 'H') not null,
	`remove_percentage` float not null,
	`remove_amount` int not null,
	`date_created` datetime not null,
    `completed` enum('N', 'Y', 'G') not null default 'N',
	primary key (`id`),
	foreign key (`user_id`) references `accounts`(`id`)
);

create table boards (
	`game_id` int not null,
	`size` enum('4', '9', '16') not null,
	`board_type` enum('S', 'O', 'L') not null,
	`board` varchar(500) not null,
	foreign key (`game_id`) references `games`(`id`),
    unique key `unique_board` (`game_id`, `board_type`)  # a combination of game_id and board_type must be unique
);

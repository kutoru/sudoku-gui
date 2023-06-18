/*
insert into `accounts` (`username`, `password`, `key`, `date_registered`)
values ('usenaem', '057304', 'not implemented kek', curdate());
insert into `accounts` (`username`, `password`, `key`, `date_registered`)
values ('usenaen', '54534', 'not implemented kek', curdate());
insert into accounts (`username`, `password`, `key`, `date_registered`)
values('aaaa', '1234nonekey', 'nonekey', curdate());
insert into accounts(`username`, `password`, `key`, `date_created`)
values('mogus', '1234', 'key', now());
insert into games(`id`, `user_id`, `empty_char`, `difficulty`, `size`, `remove_percentage`, `remove_amount`, `date_created`) 
values(5, 1, '-', 'M', '9', 56.4, 25, now());
insert into accounts(`username`, `password`, `key`, `date_created`) values('kuto', 'keywysikey', 'key', now());
*/

#insert into games(`id`, `user_id`, `empty_char`, `difficulty`, `size`, `remove_percentage`, `remove_amount`, `date_created`) values(1, 32766, '0', 'M', '9', 0.485, 39, now());insert into boards(`game_id`, `size`, `board_type`, `board`) values(1, '9', 'S', '946281537387456219152793468865932174239147856471865392694518723713624985528379641ýýýý9');insert into boards(`game_id`, `size`, `board_type`, `board`) values(1, '9', 'O', '000281507380450000150790408805000170200040800471065300000510003700624085020300641ýýýý');insert into boards(`game_id`, `size`, `board_type`, `board`) values(1, '9', 'L', '000281507380450000150790408805000170200040800471065300000510003700624085020300641ýýýý');

#insert into games(`id`, `user_id`, `empty_char`, `difficulty`, `size`, `remove_percentage`, `remove_amount`, `date_created`) values(1, 1, '0', 'M', '9', 0.481, 38, now()); insert into boards(`game_id`, `size`, `board_type`, `board`) values(1, '9', 'S', '128359476965274138437681259259163847683947521714528693396415782842796315571832964'); insert into boards(`game_id`, `size`, `board_type`, `board`) values(1, '9', 'O', '100359006065004130400001059259063007603947020704028603000400000042706000570830960'); insert into boards(`game_id`, `size`, `board_type`, `board`) values(1, '9', 'L', '100359006065004130400001059259063007603947020704028603000400000042706000570830960');
#insert into games(`id`, `user_id`, `empty_char`, `difficulty`, `size`, `remove_percentage`, `remove_amount`, `date_created`) values(2, 1, '0', 'M', '9', 0.457, 37, now()); insert into boards(`game_id`, `size`, `board_type`, `board`) values(2, '9', 'S', '938745612562918743417263859159836427386427591724159368273694185695381274841572936'); insert into boards(`game_id`, `size`, `board_type`, `board`) values(2, '9', 'O', '030700010062010040417003059059836427386007501700150360270004100005081200840072000'); insert into boards(`game_id`, `size`, `board_type`, `board`) values(2, '9', 'L', '030700010062010040417003059059836427386007501700150360270004100005081200840072000');
#insert into games(`id`, `user_id`, `empty_char`, `difficulty`, `size`, `remove_percentage`, `remove_amount`, `date_created`) values(19, 3, '0', 'M', '9', 0.458, 37, now()); insert into boards(`game_id`, `size`, `board_type`, `board`) values(19, '9', 'S', '318672594957143628246958137169835742832467951475291386691524873784319265523786419'); insert into boards(`game_id`, `size`, `board_type`, `board`) values(19, '9', 'O', '310072090050043608240908037169035042030060900000090080001004803084310065503086410'); insert into boards(`game_id`, `size`, `board_type`, `board`) values(19, '9', 'L', '310072090050043608240908037169035042030060900000090080001004803084310065503086410');
#select * from boards where `game_id` = 1 and `board_type` = 'S';
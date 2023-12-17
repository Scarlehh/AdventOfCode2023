#ifndef DATA_H
#define DATA_H

const char *test_input[] = {
	"O....#....",
	"O.OO#....#",
	".....##...",
	"OO.#O....O",
	".O.....O#.",
	"O.#..O.#.#",
	"..O..#O..O",
	".......O..",
	"#....###..",
	"#OO..#...."
};

const char *input[] = {
	"...#.#.O....#.#.OO.OOO.O..O.......O#OO#.#..#....O...#.....O.O#..O..OO..O.#...#O..#...O...##O...OO...",
	"#O....O#..O.#.#..O#...#O.O....#O.#.#O#........O...O..#.OOO#O#.......OO##O.#.OO.O.#...##.##....O#..O#",
	".O.......O.O.O.O..O.O.....#....O#..#.#O.#OO...#O.O#.O#..#O...#...O.O.......#.O....O.#..#.O##O#..O...",
	"...O....#.OO..#..OO#..##....#O.......OOOOOO...OO..#...#.O..O....#O..OO.#O...#O#...O..O#..OO....#....",
	"..O...##OOO....#..OO.OO#O##..#.#........O#.#.....#OO...#............#.###..#.#O...#..O.#O#.O#O.....#",
	"...............O.....##..O...O#.O#........#.O.#..#...#..O..O.#...#......#......O.OO.OOO.#.O.....O##.",
	"......#..#..###.OO.#......O..O.O##O..O.....OO.#.OO....O.....OO#O..O....#.....#.#.O#..O..O.OO.O#O.O.#",
	"##O.....O.#.#O...#.#O###....#.O#.#..#..O.#O........O.OO..#..#O#.O#..OO..#.O.##O....#.##O.O.......##.",
	"O#...###...O..#...#......O#.OO.....#...OOO...#.#O.#...##..OO#.......#OO.....#...O...#.#O.........O.O",
	"..O....O....OO..O.O.O........#.O#..O.#..#..OO#.OO..#.O...O..#...O..##..O........O##..........OOO..OO",
	"....##......#.#.O.O#O##.#....#..O#............#..#...#......#O.OO#....O.......O###....O...........OO",
	".O.OOO..O#....O...O..#.O#.#O.O...#.O..O#...OO#.#....#OO.#........#O.......O...#O......O...O....#...#",
	".#....#O...##..#.#..........O..#O........OOO.......O.OO.##...#..........#......#.O##.#O#OO#OO..#..O.",
	"......#O...#.#.......O........#O....#O..##....O......O.#.O..#OO............O##O....#O.OO#..O#..O#...",
	"..OO.....O#O..#OOOO#O.##.........O..#OO#......O.OO.....O......OO..O...O..O....O..O#O.......O..O.O#..",
	"....O...OO....##.....OOO...O#O.#.O...O.....#........#.#O#.....O.O.OO.###.#.OO#OO....O.....O..#.#O...",
	".OO#..O#O#O...#..O.O....O#.O.#........O.O..O....#O#....#.#.O#.#...O.O..O..#..#...OO#O......#O.O..O.#",
	"OO...O.O.#..#....#...#O.O##O#...#............##.O..OOO....O..OO....#OO....O.#....O#.O........OO..#..",
	"..O#.OO#.#O#..O.......O.##.O.#....OO#.#O#.##.O..O#..####....#..#......#...##.O##...O....O..#.#......",
	"#O.O#.....#....O...O.O..O.O.O#O.O#....#..O...#.O.#O...#..#.#O.....#O..##...O.......O.....O..OO#OO##.",
	"..O.#..#...O....#.##.#.O......#.#.##.......#.O..##O#.#O.OOO..O...#O......#..O.....O.OO...O#.O.#OO#.O",
	".#..OO#.......OO....O.##...O......O.OO#.O......#O..O#..#..O.O..O.#..OO.O.#O..O..#......O...O....O#..",
	"O....#.#O..O#...#..##..##.O.O.O..O.O#...O#..#O.O......#O.......O..O.O...#.#O..OO#.#.....#O#...O..#.O",
	"...O...O.O.O.OO..O....O..O..O##..O.........O#O..O.#...#.O..O.#........#...O........O#.#.O..O.....#..",
	"OO....O#...........#OO......O.....O...#...OO....OO..O.........O.#......##O....#...O##....O.#...#...#",
	"#OO#....#......OO.O....O...#..O...#.OOOO..OOO.O.O...O#.......O....#O#O.O#O......#...#...OO#.O...#..#",
	"....O#.#...O..#.................#.#...O...O...O.O#.##..O.#.#....####..OO....O.......#.OO.O....#...#.",
	".....O.#.#O..#O...#OO....OO...O#..O...O..#O..O....#.#O..#.......O...O.O.....#.##.#O.OO..#.#....###..",
	".#O..#...#...#.#.O.#O.#OO..#.#..#O#.#.#O#.O#O#..##..#...#O#.#..#.OO#..#..#..O...O...O..O...#.O....O.",
	"..O.....#....#O#OO#O.....O.....O...OO.O......OO..O....O...#....O....#...OO....O..O...#...###O.....#.",
	"##..##...#OOO...#.OO...#.#.O#.O.........O.O.#.O..O.OO#.O......#.###...#..#O.#....#...#.O..##...#O...",
	".O.#...O.O....O.......O...#O.....O......OO..OOO##.#...##OO.O......#....O..#..#.##.OO.......#O...#OO.",
	"...#...O#..O.#.OO.#.OO..O.#O.#.O.#...O#....O#.O#......OO.#....#..#..#..#....O.#....##...............",
	".O.O#....#.#.....O...#.O#O#.......#.#O..OO.O...#....#.....O.#.#.#..#...#...##..O.O...#O..O.#..#O....",
	".#......O..O#...O.O.##O..#.OOOO.O#O....O#...#O..OO.#.#O......#..O..O.OO#OOO#O#.O.......OO.....O...#O",
	"O##.O..OOO.#..O......#...#O#.O.O#..O.OO..#......O.O.O..O.O.OO..#....O.#O...O#.#..#..O.#...##O.O.....",
	".#OO#....#.....#..OO.OO...##.O......OOO.#O..O#.O.O.........O#.O.#.#...#..##...#O.O..OO.O#.#..O..O.O.",
	".O.....#.O#....O#.....#.O..O..O#..#..OOO#O....#OOOOO.#.#.........O#..O.#....#.#....O.#..##..#.......",
	"..O.#OO....#O.#...#O...#.O#..#.O....O.#..O....O#.....O.OO..OO.OO#.#..#..#O.O.#...O....OO...O.#..O..O",
	".O.OO#...O#.OO....#.O....O.###...#..O.....O....#.O..O.#O.O.....#....#O#O...#..O...O........O...#....",
	"#...#...#..O..#.##.#.....O#..#O.##.O...O...#....O.O.O..O.O........O.O.O.....O..#.......#...O..O.#.#O",
	"#O...#...O.#....#.O.....OOO..O...OO#OO#.......#O.##...#.O#O#....#.....O#..OO.#.#.O.O..O.#OO.O.#..O..",
	"......O.......O.#.O.#.O...........O.O.OO#....#OO........O#.......OO.O..#O...#....O#..O....OO..O##...",
	".##..O..#O...O.O....#O#..OO#O.#....#O.OO#O....#.....#...#.#OO#.OO.#.O.O.O.OO.#O.O.#.O....#O.O.O..O..",
	"O#..O#O##.O....O..#......O....#..O##O.O#...O...O...OO#..#OO...O##.#....O#.O..O.......#..#......#O..#",
	"O.OO..O..#.O..O#OO#O.....#O..O..#...#.OO.O..O...........O...O...OO##.#..O..#.#.OO.#.#...O.O......O.O",
	".O.O##.O....#O.O...O#.#..O....#O.....O..O#OO....OO##.#.O..#O.O...O..O.O...#O.OO.........#.##OO#..#..",
	"..OO....O.....#....O.....O...OOO#...#.O.........O.O..OOO.###O.#.......#.#...O.OO.#..O.....#O.....#..",
	"O...##O...O..##..#.#...#.#O#.O...#.#.O..O....##......#...#.O..O...OO.#...OOO#OO...O.O#O..OO.O##O..O.",
	"..#.OO.#.##..O....#...OO.#O.......O.O#...O..#.#O..O.###O#.#.O.O...O.#O.#..#.O..O#O#..O.........#.#..",
	"O.#.O##.......OO#....O#.......O..O.....#.........O.O.....#O.......#O..#.O...#....O.#....#......O.O.#",
	".OO.O...O.......#O#....#O#...#.........O..O.#.OO#.OO.O#...#O...O..#..O##O.#...O#..O.OO.O...#OO.##.#.",
	"...O.O...OOO.O......#..O...#.##.O..O..#...O.O...#.O.O..OO..OO..#....O.O#..#...O.OO.#.....#...OO#...#",
	".#............#O.OO..O#.....O..#O.#O.##O....O.O....O..O#..O..O.#..O.#.O.#.O.#..#O.#.OO.O......##...O",
	"#.....O.#..O.O........O#O#OO..OO.....#.#....OO##......O.O.##..##.#.O...O.#.#O......O..##.#.#.#..#O..",
	"##.#.O..O...O..OO...O....O.O..O#...OO....OO#.#...#.#....OO#..........O..O...O...O........#..O##.#.#.",
	"..OO.#..#.OO..#O..#.O...OO.O...O....#..OO....#OO..#........#...O..........#..O...OO.O.......#.#..##.",
	".#.#...#O.O.#.O..O.OO.OO#..OO#OOO#O....O..O#..OO.O..##..#.#....OOOOO#....OO..O....#..O..............",
	"...O#.OO......O.#.O.#.#O.OOO...#OO..#....#.O.O.O.......#...##...O...OOO..##...O....O...O.#...O.O...O",
	"..O...O..#.O.....#.#..##.......####...##.......O...O#.##....O.#..OO....#.#.O...##O.#O.###.OO#....O.O",
	".O#..#....OO...O.O.......O#OO..O#.O.O..#......#..O.#..#O......OO.O...O.....O........O#.#O.#.#.##.O#.",
	"..O....O.#...#..##..O...#.O#..OO...O.......#OOO......#O..OO...O...#..O...##O.#...#.#.##...O...#.OO..",
	"O.#..#...O#OO.O#.O..O.....O.O..#.#.##....O.O..O......OO.O.#.....#....#.##...#...O..O........#......#",
	".OO.OO.........#...#.#O...#..#..#.###O....#...OO#......#O.O..........#O...#.#.#O#..........#.O#...OO",
	"##.#..#O#OO.#.....O......#....O..#.O#..#.OO.........#.......#.#..#..O.O#OO.###.O.#.#O..##....O.O..O#",
	"#...O...O.......O#.O.#..#O#.O...O...O...O.O.#.O....O###..#.O..O.....O..OO#...O.#...#....O.#O..OO.O..",
	"#O...O...O.##..#.#OO.....#O.#..O....#O.O....O.....#.O.....#.O.O....#.......O.#.O..#.O.##....O..O..O#",
	"O..O.....#O..O...O........O..#.#..........##O#..#..O.#.#OOO..#..O...O..O..#.O....O...O...#...#...O..",
	"#...O.......O#..#.O#.O.....#....O#O......O..O.....#.....O...#...O...#O..#.O..#..#....O....##O#.....#",
	"O...O..#O#.OO..##..#.......O.........#......#...#..O.O..#..#O..O..O.OO......O#OO.#..O#....#.O.#.....",
	".....#.OOO..OOO....O...#O....O.#.O.#.#O..#O.......O#..O.#O.#.#..#......O#O###..#.#.O..OO.O#.##.OO#.#",
	"O...#..O#.##O..#...#.....O...O.O............O#.....#.O....O#....O#.#O#O..O#.OO..........#.O.#OOO.O..",
	"......#..#...O..O....OO#.O...OO..O....O..##O#..O#..O..##.O..#....##OO.....#..O#.O....#O.#....##.O...",
	".#..O.O..#..........O...O...O.#..O.#......O.O.....OO#..#...O.....O##..O.O..#.OO.#O.O....O...O..#..#.",
	".OO.#..O......#........#.#.O...#..........O..O.O.......OO..##O.....#...O...#..#O###..O..O.OOOOO.#.O.",
	".O..#..O..O...O..#O......OOO.O#..O#.#O...O#O.#...O....O..OO.#....#...O#................O.#O..O.#O..#",
	"......O..O...##..O..##.O.####..OO.O.......#.#O..O#..O#O.......#..O.....##........#..O..O.#...O....OO",
	".....O.O.O.....O..OO..#O..O#.#OO....#O...#O#.#.OO.#..O...O.#.....#.#O#..O#...OO##.........##...##..#",
	"....O..OOOO..O.O...#.....#.#..OOO...#OO.O#..O..O....#O.......#.O..OOO......OO...#.O#............O#.O",
	"......O....#...#.#..O.O#.#...O..O.OO##.O..O#OO##...#.#..O.OO.........#..##O#...O.#..O.#OO.#O#...##O.",
	"O..##.O...O..#.O.O.O..O.........#..O...#..O.O.##O#.O..#.#.....#..#O#..#.OOO#.O..O...OO#.O...O#......",
	".O.....O......O.......O#..O.OOOO..O..OO.O#.##.OO#O#.O......#...#.........O..O#...#O..#..#.O...O.#OO.",
	"#O.O...#..OO.#...O.O#....#..#...#OOO##.O.OO#.....#.O#.O..O.#O#O.O.O..........O#.O#.#O###O..#..#.#OO#",
	"#O###.O..O..O......#.O#.#....OO..O.O#....#...#...#.##...OO..O.#OO........O....O..O....OO......O..O.#",
	".O#O..O...#OOO...O.O...#.O#......#......#O.....O.#.#.O.#....O#.#O..#...#..#...OO#.....OOO....OO.....",
	"..O.#.O....OO......O...O..##.O........#.O.#O.#...O...O.#.##OO.#O......O...O..O.O.O.##..O#.##.#.#O...",
	".#OO#.#.O#O....O.O....OO#....##.....#.##O..O...OO.....#..O.#....O#.......O....OO.OOO.#...#..O.O.#.OO",
	".O...O....#.O..O.#..#.........O.#O#.#...O..#O.O.O..O##.....OO..O.O..OO..O..#..#.#.O..#O..O.OO##....O",
	".##...#O.O..OO..O..#.#O.O.OO.#..#.OOOO.....O...O.O.O#...O#.#.O.............O..O...#.#..........OO#.#",
	".#....##O....##O..#.O.O..#..O##....#.#.OO........O.O#..#........#OO........O...#.OO..#.........#....",
	".##OO..#O.#.O..OO.#...#O#.....O....O.#....#O..O#O.#.O..##.O.O.....#.#...#.O..OO....O....#.#.#.......",
	"O.O.O.#....#.OO.#...#...O..#.OO..#..O..#...O.OO.O...##...OO.O#O..O.OO.O##.....#..O#..#O....O.O#OO.#.",
	".#.O....#.#....#..O.O....OO......O......O.#...O...#.O.O..#.#.....O..#O.O.O..OOO#.O#..O...O#..OO.....",
	"#.#O..#....#.....O.#....#......O.O..O.O.OO.O#...O.#.O.O...#....O...#..#...O.#.O..#.O...OO.#.#O###.OO",
	"..#..O..#O##..#.....O...#..O...OO..#.#.O.#.O.O.....O..O#O#..O......#...#O.O.OO..O............#....#.",
	"....O#....O#O###O.O..#.#..O.#.O.#.O....O........#O.OOO......O.OO....O.O.O.....##.O#....##O.#.OO..O.#",
	"..#.O...OO.#O.#..OO.##..#...O#..O#..#O.O..#......O.....##....O...O.O#OO#O.......O##OOO.OO.O...O.#..#",
	"O......#.O.....OO.OO.O...O.#O..O...O.#.#...#...O...#.OO.O.#.#OO.....#.O.#....OOO........##...##.##O.",
	"#O...#....#...##O.#......O#...#O..........##O..#.O.#O#..#...OO.O....O..##..#...#...#..O..O....O..O#.",
	"...OO....O#..O..#....O.#.#.....OO.#..#O..OO.#.#.#.#......O...O..#.#..##.....#...O.##.....O#.#..O#O.."
};

#endif

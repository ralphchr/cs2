// Rebuild with: node scripts/build-readme.cjs
// Font outlines and typography helpers come from Ralph's profile README project.
// Outputs are self-contained SVGs: no font downloads or browser dependencies.
const fs = require('node:fs');
const path = require('node:path');
const {SVG} = require('./readme-lib/svg.cjs');
const {typingTitle} = require('./readme-lib/typing.cjs');
const {light} = require('./readme-lib/theme.cjs');
const output = path.resolve(__dirname, '../assets/readme');
const C = {ivory:'#F0E9DD', silver:'#C5C6D0', blue:'#8EBBEE', purple:'#8B5CF6', red:'#EF7583'};

function grid(s) {
  s.add(`<defs><pattern id="terminal-grid" width="48" height="48" patternUnits="userSpaceOnUse"><path d="M48 0H0V48" fill="none" stroke="${C.blue}" stroke-opacity=".045"/><circle cx="1" cy="1" r="1" fill="${C.purple}" fill-opacity=".2"/></pattern></defs><rect width="${s.w}" height="${s.h}" fill="url(#terminal-grid)"/>`);
}

function wordLine(s, text, x, y, size, color, outline = false) {
  let at = x;
  return text.split(' ').map(word => {
    const art = s.text(word, at, y, size, 'display', color, -1, outline);
    at += s.measure(word, size, 'display', -1) + size * .38;
    return art;
  }).join('');
}

function hero(mobile, animated) {
  const w = mobile ? 600 : 1200, h = mobile ? 360 : 430, p = mobile ? 30 : 48;
  const size = mobile ? 43 : 82, topY = mobile ? 145 : 193, bottomY = mobile ? 211 : 291;
  const s = new SVG(w, h, 'COMPUTER SCIENCE. YEAR TWO.', 'Ralphchr / UP Cebu. Second-year machine problems, homework, and projects. Inter Black and JetBrains Mono lettering, with a typing cursor and brief chromatic glitches.');
  grid(s);
  s.add(`<path d="M${p} 86H${w-p}M${p} ${h-48}H${w-p}" stroke="${C.silver}" stroke-opacity=".22"/>`);
  s.add(s.text('RC', p, 61, mobile ? 34 : 44));
  s.add(s.text('_', p + s.measure('RC', mobile ? 34 : 44) - 1, 61, mobile ? 34 : 44, 'display', C.blue));
  s.add(s.text('CS2 / UP CEBU', w-p, 57, mobile ? 16 : 17, 'mono', C.blue, .6, false, 'end'));
  if (!mobile) s.add(s.text('SECOND-YEAR COURSEWORK', 161, 56, 17, 'mono', C.silver, .8));
  const top = 'COMPUTER SCIENCE.', bottom = 'YEAR TWO.';
  const topArt = wordLine(s, top, p, topY, size, C.silver, true);
  const bottomArt = wordLine(s, bottom, p, bottomY, size, C.ivory);
  s.add(typingTitle(s, [
    {text:top, art:`<g id="headline-outline">${topArt}</g>`, baseline:topY},
    {text:bottom, art:`<g id="headline-solid">${bottomArt}</g>`, baseline:bottomY}
  ], animated, p, size));
  if (animated) {
    s.add(`<defs><clipPath id="blue-slice"><rect x="${p}" y="${bottomY-size*.56}" width="${w-p*2}" height="4"/></clipPath><clipPath id="red-slice"><rect x="${p}" y="${bottomY-size*.24}" width="${w-p*2}" height="3"/></clipPath></defs>`);
    for (const [id, dx, color] of [['blue-slice', 8, C.blue], ['red-slice', -7, C.red]]) {
      s.add(`<g clip-path="url(#type-line-1)"><g clip-path="url(#${id})" opacity="0">${wordLine(s,bottom,p+dx,bottomY,size,color)}<animate attributeName="opacity" values="0;0;.85;0;.5;0" keyTimes="0;.86;.89;.92;.96;1" calcMode="discrete" dur="2s" repeatCount="indefinite"/></g></g>`);
    }
    s.parts = s.parts.map(part => part.replace('<g id="headline-solid">', '<g id="headline-solid"><animateTransform attributeName="transform" type="translate" values="0 0;0 0;2 0;-2 0;0 0" keyTimes="0;.88;.91;.95;1" calcMode="discrete" dur="2s" repeatCount="indefinite"/>'));
  }
  if (mobile) {
    s.add(s.text('Machine problems, homework,', p, 258, 18, 'mono', C.silver));
    s.add(s.text('and projects.', p, 284, 18, 'mono', C.silver));
  } else {
    s.add(s.text('Machine problems, homework, and projects.', p, 342, 22, 'mono', C.silver));
    s.add(s.text('02', w-p, 290, 116, 'display', C.purple, -3, true, 'end'));
  }
  s.add(s.text('C / C++ / HASKELL / PROLOG / DEEDS', p, h-20, mobile ? 14 : 15, 'mono', C.blue, .1));
  if (!mobile) s.add(s.text('@RALPHCHR', w-p, h-20, 15, 'mono', C.silver, .4, false, 'end'));
  s.add(`<path d="M${w-p-26} 106h26v26M${p} ${bottomY+19}v10h22" fill="none" stroke="${C.purple}" stroke-opacity=".6"/>`);
  return s.finish();
}

function toolkit() {
  const s = new SVG(1200, 352, 'The toolkit', 'C and C++ for data structures. Haskell for functions and lists. Prolog for facts and rules. DEEDS for circuits and truth tables.');
  grid(s);
  const entries = [
    ['C / C++', 'Pointers, classes & data structures', 'ARRAYS / VECTORS / STACKS'],
    ['Haskell', 'Functions, recursion & lists', 'MAP / FILTER / FOLDS'],
    ['Prolog', 'Facts, rules & relationships', 'PREDICATES / QUERIES / LOGIC'],
    ['DEEDS', 'Digital circuits & truth tables', 'ADDERS / SUBTRACTORS / SIMULATION']
  ];
  entries.forEach(([name, description, topics], i) => {
    const x = i%2 ? 636 : 48, y = i<2 ? 62 : 230;
    s.add(s.text(name, x, y, 35, 'display', C.ivory, -.5));
    s.add(s.text(description, x, y+41, 17, 'mono', C.silver));
    s.add(s.text(topics, x, y+77, 14, 'mono', C.blue));
    s.add(`<path d="M${x} ${y+100}h${i%2 ? 516 : 504}" stroke="${C.purple}" stroke-opacity=".4"/>`);
  });
  return s.finish();
}

function write(stem, svg) {
  fs.writeFileSync(path.join(output, stem+'.svg'), svg);
  fs.writeFileSync(path.join(output, stem+'-light.svg'), light(svg));
}
fs.mkdirSync(output, {recursive:true});
for (const mobile of [false, true]) {
  const suffix = mobile ? '-mobile' : '';
  write('hero'+suffix, hero(mobile, false));
  write('hero'+suffix+'-animated', hero(mobile, true));
}
write('toolkit', toolkit());
console.log('Built 10 README SVGs with profile fonts, theme variants, and motion fallbacks.');

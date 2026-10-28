#!/usr/bin/env node
/*
 * Deterministic GBA graphics conversion, not generated artwork.
 * Shadow Mewtwo pixels come from the Pokemon Insurgence Wiki donor PNGs;
 * Mewsion pixels come from PRU's already-imported AlteRed battle sprite.
 *
 * ImageMagick does the scaling. This exporter writes indexed PNGs with one
 * fixed palette so front, back and overworld use identical colour indices.
 * It also derives the Insurgence shiny palette from paired original pixels.
 * Run: node tools/pru/build_pru_shadow_art.js
 */
const fs = require('node:fs');
const path = require('node:path');
const zlib = require('node:zlib');
const {spawnSync} = require('node:child_process');

const root = path.resolve(__dirname, '../..');
const mewtwo = path.join(root, 'graphics/pokemon/mewtwo');
const mewsion = path.join(root, 'graphics/pokemon/mewsion');
const rgb = hex => [parseInt(hex.slice(1, 3), 16), parseInt(hex.slice(3, 5), 16), parseInt(hex.slice(5, 7), 16)];
const palette = [
    '#FFFFFF', // transparent (alpha is tracked separately)
    '#000000', '#181818', '#262728', '#363739', '#42454A', '#525860',
    '#D36800', '#FFA54D', '#FFC974', '#D679D6', '#E590D1', '#CED2D7',
    '#FFFFFF', '#D05DB5', '#DEDEDE',
].map(rgb);

function convert(source, transforms, width, height) {
    const args = [source, ...transforms, '-depth', '8', 'RGBA:-'];
    const result = spawnSync('convert', args, {maxBuffer: 16 * 1024 * 1024});
    if (result.status !== 0) throw Error(`ImageMagick: ${result.stderr.toString()}`);
    if (result.stdout.length !== width * height * 4)
        throw Error(`Invalid ${width}x${height} RGBA data from ${source}: ${result.stdout.length}`);
    return result.stdout;
}

function resize(source, width, height, spriteW, spriteH) {
    return convert(source, [
        '-trim', '-filter', 'point', '-resize', `${spriteW}x${spriteH}`,
        '-background', 'none', '-gravity', 'south', '-extent', `${width}x${height}`,
    ], width, height);
}

function nearest(pixel, colors) {
    if (pixel[3] < 128) return 0;
    let best = 1;
    let bestDist = Infinity;
    for (let i = 1; i < colors.length; i++) {
        const dist = (pixel[0] - colors[i][0]) ** 2
            + (pixel[1] - colors[i][1]) ** 2
            + (pixel[2] - colors[i][2]) ** 2;
        if (dist < bestDist) [best, bestDist] = [i, dist];
    }
    return best;
}

function indices(rgba, colors) {
    const out = Buffer.alloc(rgba.length / 4);
    for (let i = 0; i < out.length; i++) out[i] = nearest(rgba.subarray(i * 4, i * 4 + 4), colors);
    return out;
}

function repeatFrames(frame, count) {
    return Buffer.concat(Array.from({length: count}, () => frame));
}

function repeatHorizontal(frame, width, height, count) {
    const output = Buffer.alloc(width * count * height);
    for (let y = 0; y < height; y++)
        for (let frameIndex = 0; frameIndex < count; frameIndex++)
            frame.copy(output, y * width * count + frameIndex * width, y * width, (y + 1) * width);
    return output;
}

const crcTable = Array.from({length: 256}, (_, i) => {
    let crc = i;
    for (let j = 0; j < 8; j++) crc = (crc >>> 1) ^ ((crc & 1) ? 0xEDB88320 : 0);
    return crc >>> 0;
});

function chunk(kind, bytes) {
    const type = Buffer.from(kind, 'ascii');
    const len = Buffer.alloc(4);
    len.writeUInt32BE(bytes.length);
    const crcSource = Buffer.concat([type, bytes]);
    let crc = 0xFFFFFFFF;
    for (const byte of crcSource) crc = crcTable[(crc ^ byte) & 0xFF] ^ (crc >>> 8);
    const tail = Buffer.alloc(4);
    tail.writeUInt32BE((crc ^ 0xFFFFFFFF) >>> 0);
    return Buffer.concat([len, crcSource, tail]);
}

function png(filename, width, height, pixels, colors) {
    if (pixels.length !== width * height) throw Error(`Invalid pixel count for ${filename}`);
    if (colors.length !== 16) throw Error(`Expected GBA palette of 16 colours for ${filename}`);
    const ihdr = Buffer.alloc(13);
    ihdr.writeUInt32BE(width, 0);
    ihdr.writeUInt32BE(height, 4);
    ihdr[8] = 8; // indexed 8 bits on disk, constrained to sixteen GBA indices
    ihdr[9] = 3;
    const scanlines = Buffer.alloc((width + 1) * height);
    for (let y = 0; y < height; y++) pixels.copy(scanlines, y * (width + 1) + 1, y * width, (y + 1) * width);
    fs.writeFileSync(filename, Buffer.concat([
        Buffer.from('89504e470d0a1a0a', 'hex'),
        chunk('IHDR', ihdr),
        chunk('PLTE', Buffer.from(colors.flat())),
        chunk('tRNS', Buffer.from([0, ...Array(15).fill(255)])),
        chunk('IDAT', zlib.deflateSync(scanlines, {level: 9})),
        chunk('IEND', Buffer.alloc(0)),
    ]));
}

function readPal(filename) {
    const lines = fs.readFileSync(filename, 'utf8').trim().split(/\r?\n/);
    if (lines[0] !== 'JASC-PAL' || lines[2] !== '16') throw Error(`Bad palette ${filename}`);
    return lines.slice(3, 19).map(row => row.trim().split(/\s+/).map(Number));
}

function writePal(filename, colors) {
    fs.writeFileSync(filename, ['JASC-PAL', '0100', '16', ...colors.map(c => c.join(' ')), ''].join('\r\n'));
}

function donorShinyPalette() {
    const votes = Array.from({length: 16}, () => new Map());
    for (const side of ['front', 'back']) {
        const normal = convert(path.join(mewtwo, `insurgence_shadow_${side}_source.png`), [], 160, 160);
        const shiny = convert(path.join(mewtwo, `insurgence_shadow_shiny_${side}_source.png`), [], 160, 160);
        for (let at = 0; at < normal.length; at += 4) {
            if (normal[at + 3] < 128 || shiny[at + 3] < 128) continue;
            const index = nearest(normal.subarray(at, at + 4), palette);
            const color = Array.from(shiny.subarray(at, at + 3)).join(',');
            votes[index].set(color, (votes[index].get(color) || 0) + 1);
        }
    }
    return palette.map((normal, index) => {
        const pairs = [...votes[index].entries()].sort((a, b) => b[1] - a[1]);
        return pairs.length ? pairs[0][0].split(',').map(Number) : normal;
    });
}

function main() {
    writePal(path.join(mewtwo, 'normal.pal'), palette);
    writePal(path.join(mewtwo, 'shiny.pal'), donorShinyPalette());

    const front = indices(resize(path.join(mewtwo, 'insurgence_shadow_front_source.png'), 64, 64, 64, 60), palette);
    const back = indices(resize(path.join(mewtwo, 'insurgence_shadow_back_source.png'), 64, 64, 64, 60), palette);
    const animated = repeatFrames(front, 2);
    for (const filename of ['anim_front.png', 'anim_front_gba.png']) png(path.join(mewtwo, filename), 64, 128, animated, palette);
    for (const filename of ['back.png', 'back_gba.png']) png(path.join(mewtwo, filename), 64, 64, back, palette);

    const follower = indices(resize(path.join(mewtwo, 'insurgence_shadow_front_source.png'), 32, 32, 30, 30), palette);
    png(path.join(mewtwo, 'overworld.png'), 192, 32, repeatHorizontal(follower, 32, 32, 6), palette);

    const iconPalette = readPal(path.join(root, 'graphics/pokemon/icon_palettes/pal2.pal'));
    const icon = indices(resize(path.join(mewtwo, 'insurgence_shadow_front_source.png'), 32, 32, 31, 31), iconPalette);
    for (const filename of ['icon.png', 'icon_gba.png']) png(path.join(mewtwo, filename), 32, 64, repeatFrames(icon, 2), iconPalette);

    const fusionPalette = readPal(path.join(mewsion, 'normal.pal'));
    const fusion = indices(resize(path.join(mewsion, 'front.png'), 32, 32, 30, 30), fusionPalette);
    png(path.join(mewsion, 'overworld.png'), 192, 32, repeatHorizontal(fusion, 32, 32, 6), fusionPalette);
}

main();

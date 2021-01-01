// RUN: llvm-mc -arch=amdgcn -mcpu=gfx1010 -mattr=+wavefrontsize32,-wavefrontsize64 -show-encoding %s | FileCheck --check-prefixes=GFX10,W32 %s
// RUN: llvm-mc -arch=amdgcn -mcpu=gfx1010 -mattr=-wavefrontsize32,+wavefrontsize64 -show-encoding %s | FileCheck --check-prefixes=GFX10,W64 %s

//===----------------------------------------------------------------------===//
// ENC_FLAT.
//===----------------------------------------------------------------------===//

flat_load_ubyte v5, v[1:2]
// GFX10: encoding: [0x00,0x00,0x20,0xdc,0x01,0x00,0x7d,0x05]

flat_load_sbyte v5, v[1:2]
// GFX10: encoding: [0x00,0x00,0x24,0xdc,0x01,0x00,0x7d,0x05]

flat_load_ushort v5, v[1:2]
// GFX10: encoding: [0x00,0x00,0x28,0xdc,0x01,0x00,0x7d,0x05]

flat_load_sshort v5, v[1:2]
// GFX10: encoding: [0x00,0x00,0x2c,0xdc,0x01,0x00,0x7d,0x05]

flat_load_dword v5, v[1:2]
// GFX10: encoding: [0x00,0x00,0x30,0xdc,0x01,0x00,0x7d,0x05]

flat_load_dwordx2 v[5:6], v[1:2]
// GFX10: encoding: [0x00,0x00,0x34,0xdc,0x01,0x00,0x7d,0x05]

flat_load_dwordx3 v[5:7], v[1:2]
// GFX10: encoding: [0x00,0x00,0x3c,0xdc,0x01,0x00,0x7d,0x05]

flat_load_dwordx4 v[5:8], v[1:2]
// GFX10: encoding: [0x00,0x00,0x38,0xdc,0x01,0x00,0x7d,0x05]

flat_store_byte v[1:2], v2
// GFX10: encoding: [0x00,0x00,0x60,0xdc,0x01,0x02,0x7d,0x00]

flat_store_short v[1:2], v2
// GFX10: encoding: [0x00,0x00,0x68,0xdc,0x01,0x02,0x7d,0x00]

flat_store_dword v[1:2], v2
// GFX10: encoding: [0x00,0x00,0x70,0xdc,0x01,0x02,0x7d,0x00]

flat_store_dwordx2 v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0x74,0xdc,0x01,0x02,0x7d,0x00]

flat_store_dwordx3 v[1:2], v[2:4]
// GFX10: encoding: [0x00,0x00,0x7c,0xdc,0x01,0x02,0x7d,0x00]

flat_store_dwordx4 v[1:2], v[2:5]
// GFX10: encoding: [0x00,0x00,0x78,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_swap v[1:2], v2
// GFX10: encoding: [0x00,0x00,0xc0,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_cmpswap v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0xc4,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_add v[1:2], v2
// GFX10: encoding: [0x00,0x00,0xc8,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_sub v[1:2], v2
// GFX10: encoding: [0x00,0x00,0xcc,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_smin v[1:2], v2
// GFX10: encoding: [0x00,0x00,0xd4,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_umin v[1:2], v2
// GFX10: encoding: [0x00,0x00,0xd8,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_smax v[1:2], v2
// GFX10: encoding: [0x00,0x00,0xdc,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_umax v[1:2], v2
// GFX10: encoding: [0x00,0x00,0xe0,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_and v[1:2], v2
// GFX10: encoding: [0x00,0x00,0xe4,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_or v[1:2], v2
// GFX10: encoding: [0x00,0x00,0xe8,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_xor v[1:2], v2
// GFX10: encoding: [0x00,0x00,0xec,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_inc v[1:2], v2
// GFX10: encoding: [0x00,0x00,0xf0,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_dec v[1:2], v2
// GFX10: encoding: [0x00,0x00,0xf4,0xdc,0x01,0x02,0x7d,0x00]

flat_atomic_swap_x2 v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0x40,0xdd,0x01,0x02,0x7d,0x00]

flat_atomic_cmpswap_x2 v[1:2], v[2:5]
// GFX10: encoding: [0x00,0x00,0x44,0xdd,0x01,0x02,0x7d,0x00]

flat_atomic_add_x2 v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0x48,0xdd,0x01,0x02,0x7d,0x00]

flat_atomic_sub_x2 v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0x4c,0xdd,0x01,0x02,0x7d,0x00]

flat_atomic_smin_x2 v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0x54,0xdd,0x01,0x02,0x7d,0x00]

flat_atomic_umin_x2 v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0x58,0xdd,0x01,0x02,0x7d,0x00]

flat_atomic_smax_x2 v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0x5c,0xdd,0x01,0x02,0x7d,0x00]

flat_atomic_umax_x2 v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0x60,0xdd,0x01,0x02,0x7d,0x00]

flat_atomic_and_x2 v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0x64,0xdd,0x01,0x02,0x7d,0x00]

flat_atomic_or_x2 v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0x68,0xdd,0x01,0x02,0x7d,0x00]

flat_atomic_xor_x2 v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0x6c,0xdd,0x01,0x02,0x7d,0x00]

flat_atomic_inc_x2 v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0x70,0xdd,0x01,0x02,0x7d,0x00]

flat_atomic_dec_x2 v[1:2], v[2:3]
// GFX10: encoding: [0x00,0x00,0x74,0xdd,0x01,0x02,0x7d,0x00]

// Also see flat-gfx10.s, flat-global.s, flat-scratch-instructions.s.

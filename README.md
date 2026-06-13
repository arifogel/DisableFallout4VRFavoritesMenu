# DisableFallout4VRFavoritesMenu

An automated, low-overhead F4SEVR plugin engineered to completely suppress the real-time gameplay
activation of the radial Favorites Wheel in **Fallout 4 VR**.

This mod eliminates accidental menu popups during intensive world interactions, making it an
indispensable immersion improvement.

---

## 🎯 The Core Functionality

- **Complete Wheel Suppression:** The plugin intercepts and blocks the real-time holographic
  Favorites Wheel from opening in the game world.
- **Pip-Boy Compatibility Intact:** This mod **does not** prevent you from favoriting or managing
  your gear. You can still assign items, weapons, and consumables to your favorites slots normally
  from inside your Pip-Boy interface.

---

## 🛑 The Problem: HTC Vive Wand Input Coupling

This plugin was specifically designed to solve a severe control limitation plaguing **HTC Vive
Wand** users.

In vanilla Fallout 4 VR, the **"Activate"** action (picking up items, talking to NPCs, opening
doors) and the **"Favorites Menu"** action are inextricably coupled to the same input on the Vive
wand right trackpad. This architectural coupling introduces major mechanical friction:

1. When attempting a standard world activation, if you miss the object due to intervening minor
   movement you will accidentally trigger the radial favorites overlay instead.
2. If your thumb slides a bit on release you may accidentally use or equip an item from some
   favorites slot. You might think to work around this by keeping the favorites wheel empty;
   however, the game will automatically populate an empty wheel when certain objects are picked up,
   e.g. stimpacks.

### Why Software Rebinding Fails:

- **MCM** You cannot decouple these actions using the Fallout 4 VR controls mod, because whatever is
  bound to favorites and whatever is bound to activate will both send the same coupled input to the
  game engine. So both bindings will trigger activate when an object is selected on screen, and both
  bindings will trigger the favorites wheel otherwise.
- **SteamVR** For the exact same reason, standard SteamVR Input remapping profiles are completely
  incapable of separating these mechanisms. SteamVR merely passes input primitives to the game
  engine, where the actions remain fused inside the executable's input system.
- This plugin resolves the issue by simply disabling the branch of the handler for that input that
  opens the favorites wheel.

With the advent of physical, modern VR immersion frameworks, the traditional UI-driven favorites
wheel has become completely superfluous. This plugin is explicitly intended to be combined with
spatial weapon management mods and full body frameworks such as
[Virtual Holsters](https://www.nexusmods.com/fallout4/mods/51224) and
[FRIK](https://www.nexusmods.com/fallout4/mods/53464). By combining this plugin with a layout like
Virtual Holsters, you can completely eliminate archaic radial menu wheels from your gameplay loop.
Weapons can be drawn physically from your shoulders, hips, or chest, while item interactions remain
responsive and accidental UI popups are permanently removed.

# Installation

1. Pull the [latest version of this mod from Nexus](https://www.nexusmods.com/fallout4/mods/106100)
   or from the
   [GitHub releases page](https://github.com/arifogel/DisableFallout4VRFavoritesMenu/releases)
2. Install via your favorite mod manager, OR manually install (if you hate yourself) by extracting
   into your Fallout 4 VR installation's Data folder.

# Acknowledgements

This plugin relies entirely on the structural foundations engineered by the Script Extender
development community. The core prerequisites for running this mod are a valid Steam release of
Fallout 4 VR and the Fallout 4 Script Extender VR (F4SEVR) [[Homepage]](https://f4se.silverlock.org)
[[GitHub]](https://github.com/ianpatt/f4se). Immense credit and gratitude go to ianpatt and the
Silverlock Team for their exceptional reverse-engineering efforts and software contributions. Their
tireless work provides the core native API hooks that make advanced plugin development possible for
the entire Fallout 4 and VR modding ecosystem.

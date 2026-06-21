# 🧸🛣️🧸 Stitched Together : Fulff on the Road 🧸🛣️🧸

An atmospheric, co-op road trip mystery built from scratch in C++26 and OpenGL 3.3.

Journey through an eerie, empty wilderness, manage your vehicle as a crew, and document your findings to uncover why civilization vanished. 

(looks like it has been centuries since it has been wiped, massive gaps (because of tectonic plates), nature recovering everything (everything but the main camp))

(Inspired by *Jalopy*, *Pacific Drive*, and *Firewatch*. Designed with optimization-first architecture to run smoothly on lower-end harware such as Intel UHD 620 integrated graphics)

## 🏕️ The Premise 

You are a firewatcher stationed deep within an isolated, sprawling wilderness. The game begins as your summer shift ends; you pack your gear and drive down the long forest road back toward the city, only to discover an usettling truth : **everyone is gone**. With no answers left behind, you turn your vehicle around and head back to your started base camp. The road ahead is long, divided by mysterious borders, and littered with the remnants of an empty world waiting for you to uncover its secrets. 

## 🕹️ Core Gameplay Loops & Features

### 🗺️ Seamless Frontier Regions
The world is split into distinct, procedurally generated regional sandboxes separated by massive physical **Frontier Gates** (quarantine blockades, mountain tunnels, and winding canyons).
- **Seamless Loading Corridors :** Driving into a frontier locks the vehicle in an enclosed buffer zone. While inside, the engine completely drops the previous world from memory and generates the upcoming region on a asynchronous background thread, eliminating hard loading screens entirely without hitching frames.

### 🚙 One Shared Van (Co-Op Mechanics)
Survive alone or journey together with friends **Local or Online Co-Op**. Players share **one chunky, highly customizable van**
- Forces true crew teamwork : One player handles the wheel, another navigates with a physical map and compass, another monitors, and another scrambles out to scavenge roadside junk.

### 😴 Exhaustion & Driver Rotation
Driving down the long, empty roads causes physical fatigue. The active driver's stamina will steadily deplete, causing their vision to blur, narrow, and periodically fade to black as the experience "micro-naps".
- To prevent a catastrophic crash, the crew must actively manage sleep schedules. Players must physically stop the van to swap seats, allow the tired driver to recover by sleeping in the passenger seats, or pass up scavenged coffee items to stay awake just long enough to reach the next safe zone. 

### 🏠 Regional Lookout Bases
Every frontier region contains a prominent structural landmark (like a prominent Firetower or Ranger Station).
- Clearing and cleaning a base camp establishes a permanent checkpoint within that procedural region. Use bases to build secure item stashes, swap out major vehicule configurations, or use the beds to completely restore the entire party's stamina before pushing through the next frontier.

### 📔 Journaling System
The core narrative progression is driven by your **Daily Journal**. Since the world is completely unpopulated, you aren't hunting NPCs; you are hunting answers. Pull over to photograph environmental anomalies, collect discarded documents, or sketch strange structures. Filling your journal acts as your primary objective and survival log.

## 🔧 Technical Architecture & Optimization

To ensure a locked 60 FPS on integrated mobile GPUs, the custom engine architecture implements strict low-overhead data lifecycles : 

- **Asynchronous VFS (Virtual File System) :** Assets are categorized into isolated, independent `.pak` archives. The engine strictly loads and unloads modules on demand, keeping RAM usage lean.
- ...

## 🧰 Software Stack

- **Language Standard :** C++26
- **Graphics API :** OpenGL 3.3 (Core Profile)
- **Windowing & Input :** GLFW 3.4
- **OpenGL Loader :** [GLAD](https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D3.3&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=core&extensions=GL_KHR_debug&loader=on)
- **Mathematics :** GLM (OpenGL Mathematics)
- **Automation :** Python 3 (For cross-platform asset package compilation)

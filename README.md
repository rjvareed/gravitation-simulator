# What is this?
This is a gravitation / n-body problem simulator. It simulates and displays particles moving in accordance to Newton's law of gravitation. It's written in C and uses GTK, specifically cairo for its graphics. It uses pthreads to handle drawing. It's meant to be run on Linux. 

The program is essentially performing numerical integration. It does this by using a (computationally better) formulation of Newton's laws of gravitation called the Hamiltonian formulation. This formulation gives us two (relatively simple) first order differential equations in time for each coordinate and particle, one for position and one for momentum:

$$\frac{d x}{d t} = \frac{d H}{d p_x}$$

$$\frac{d y}{d t} = \frac{d H}{d p_y}$$

$$\frac{d p_x}{d t} = -\frac{d H}{d x}$$

$$\frac{d p_y}{d t} = -\frac{d H}{d y}$$

Where H is the Hamiltonian, in this case

$$H=\sum_i \frac{p_i^2}{2m_i}-\sum_{i \neq j} G\frac{m_i m_j}{\sqrt{(x_i-x_j)^2+(y_i-y_j)^2}}$$

This is much easier to integrate than the second order differential equations given by Newton's 2nd law. The positions of the particles for each time slice are saved into memory and displayed using a timer.

# Instructions for compiling and running via command line:
This program is meant to be run on Linux and requires libgtk-3-dev.

```sudo apt install libgtk-3-dev```

```make```

```./app```

Wait a few seconds for it step through its calculations, then a window will pop up showing the particles.

Let me know if you have any problems.

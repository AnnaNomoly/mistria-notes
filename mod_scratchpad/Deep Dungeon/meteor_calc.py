import math

def calculate_trap_damage(distance: float) -> int:
    lethal_radius = 32.0
    max_distance = 256.0

    if distance <= lethal_radius:
        return 100

    if distance >= max_distance:
        return 1

    # Normalize distance outside lethal zone
    t = (distance - lethal_radius) / (max_distance - lethal_radius)

    # Exponential falloff (adjust exponent for feel)
    """
    1.0	Linear (predictable)
    1.5	Slightly punishing
    2.0	Strong dropoff
    2.5	Roguelike spicy
    3.0+	Brutal center, safe edges
    """
    exponent = 2.5
    damage = 100.0 * math.pow(1.0 - t, exponent)

    return max(1, int(damage))

i = 0
distances = []

while i < 256:
    distances.append(i)
    i += 8

for d in distances:
    print(str(d) + ": " + str(calculate_trap_damage(d)))


"""
Distance	Exp 1.0 (Linear)	Exp 1.5	    Exp 2.0	    Exp 2.5	    Exp 3.0
32	        100%	            100%	    100%	    100%	    100%
64	        86%	                80%	        75%	        70%	        65%
96	        71%	                60%	        51%	        43%	        36%
112	        64%	                51%	        41%	        33%	        26%
160	        43%	                28%	        18%	        12%	        8%
200	        25%	                13%	        6%	        3%	        2%
224	        14%	                5%	        2%	        1%	        1%
256	        1%	                1%	        1%	        1%	        1%
"""

# ==========================================

# import numpy as np
# import matplotlib.pyplot as plt

# lethal = 32
# max_dist = 256

# distances = np.linspace(lethal, max_dist, 500)

# def damage(distance, exp):
#     t = (distance - lethal) / (max_dist - lethal)
#     return 100 * (1 - t) ** exp

# for exp in [1.0, 1.5, 2.0, 2.5, 3.0]:
#     plt.plot(distances, damage(distances, exp), label=f"exp={exp}")

# plt.legend()
# plt.xlabel("Distance")
# plt.ylabel("Damage %")
# plt.show()
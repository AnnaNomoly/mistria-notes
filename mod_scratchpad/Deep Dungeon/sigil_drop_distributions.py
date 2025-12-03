import matplotlib.pyplot as plt
import numpy as np

# Groups and their probability distributions
groups = [
    'Wood\n50/25/0/0',
    'Copper\n75/50/10/0',
    'Silver\n100/50/25/0',
    #'Gold\n100/100/50/25',
    'Gold\n100/100/25/10',
    #'100/100/50/10',
    #'75/50/25/0',
    #'100/75/25/0'
]

S0 = [0.375, 0.1125, 0, 0] #[0.375, 0.1125, 0, 0, 0, 0, 0.09375, 0]
S1 = [0.5, 0.4625, 0.375, 0] #[0.5, 0.4625, 0.375, 0, 0, 0, 0.40625, 0.1875]
S2 = [0.125, 0.3875, 0.5, 0.675] #[0.125, 0.3875, 0.5, 0.375, 0.675, 0.45, 0.40625, 0.625]
S3 = [0, 0.0375, 0.125, 0.3] #[0, 0.0375, 0.125, 0.5, 0.3, 0.5, 0.09375, 0.1875]
S4 = [0, 0, 0, 0.025] #[0, 0, 0, 0.125, 0.025, 0.05, 0, 0]

# Expected values for each group
expected = [0.75, 1.35, 1.75, 2.35] #[0.75, 1.35, 1.75, 2.75, 2.35, 2.60, 1.50, 2.00]

# Stack probabilities for plotting
distributions = np.array([S0, S1, S2, S3, S4])

# Plot
fig, ax = plt.subplots(figsize=(12, 6))
bar_width = 0.15
x = np.arange(len(groups))

colors = ['#ff9999', '#66b3ff', '#99ff99', '#ffcc99', '#c2c2f0']
labels = ['0 successes', '1 success', '2 successes', '3 successes', '4 successes']

for i in range(5):
    ax.bar(x + i*bar_width, distributions[i], width=bar_width, color=colors[i], label=labels[i])

# Overlay expected value as a line
ax.plot(x + 2*bar_width, expected, color='black', marker='o', linestyle='-', linewidth=2, label='Expected Value')

ax.set_xticks(x + 2*bar_width)
ax.set_xticklabels(groups, rotation=45)
ax.set_ylabel('Probability / Expected Value')
ax.set_title('Probability Distribution of Successes per Group with Expected Value')
ax.legend()
plt.tight_layout()
plt.show()
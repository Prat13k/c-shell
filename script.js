// Radar Chart for Skills
const ctx = document.getElementById('skillsChart').getContext('2d');
const skillsChart = new Chart(ctx, {
  type: 'radar',
  data: {
    labels: ['Coding', 'Data Analysis', 'Visualization', 'Statistics', 'AI/ML'],
    datasets: [{
      label: 'Skill Proficiency',
      data: [90, 85, 80, 75, 95],
      backgroundColor: 'rgba(245, 108, 14, 0.2)',
      borderColor: '#f56c0e',
      borderWidth: 2
    }]
  },
  options: {
    scale: {
      ticks: {
        beginAtZero: true
      }
    }
  }
});
